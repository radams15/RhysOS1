BITS 32

%define SCR_SIZ 2000    ; 80 x 25 Characters - VGA Text-mode Display size
%define DISP_ADDR 0xB8000 ; the address of the display

MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot

GLOBAL _Start:function

extern main ; main c file
%include "Interrupts.asm"

SECTION .text

; BEGIN - Multiboot Header
MultibootSignature dd 464367618
MultibootFlags dd 3
MultibootChecksum dd -464367621
MultibootGraphicsRuntime_VbeModeInfoAddr dd 2147483647
MultibootGraphicsRuntime_VbeControlInfoAddr dd 2147483647
MultibootGraphicsRuntime_VbeMode dd 2147483647
MultibootInfo_Memory_High dd 0
MultibootInfo_Memory_Low dd 0
; END - Multiboot Header

MultibootInfo_Structure dd 0

; BEGIN - Kernel stack space allocation
Kernel_Stack_End:
	TIMES 65535 db 0
Kernel_Stack_Start:
; END - Kernel stack space allocation

; BEGIN - GDT allocations
; This is the GDT table pre-filled with the entries we want
GDT_Contents:
; I have a suspicion that the order of the items in the GDT matters
;	Code and data selectors first then TSS
db 0, 0, 0, 0, 0, 0, 0, 0			; Offset: 0  - Null selector - required
db 255, 255, 0, 0, 0, 0x9A, 0xCF, 0	; Offset: 8  - KM Code selector - covers the entire 4GiB address range
db 255, 255, 0, 0, 0, 0x92, 0xCF, 0	; Offset: 16 - KM Data selector - covers the entire 4GiB address range
db 255, 255, 0, 0, 0, 0xFA, 0xCF, 0	; Offset: 24 - UM Code selector - covers the entire 4GiB address range
db 255, 255, 0, 0, 0, 0xF2, 0xCF, 0	; Offset: 32 - UM Data selector - covers the entire 4GiB address range

;					   Size - Change iff adding/removing rows from GDT contents
;					   Size = Total bytes in GDT - 1
GDT_Pointer db 39, 0, 0, 0, 0, 0
; END - GDT allocations

_Start:

	cli

	; MultiBoot compliant loader provides info in registers:
	; EBX = MultiBoot Info Structure Pointer
	; EAX = 0x2BADBOO2

	; BEGIN - Multiboot Info
	mov dword ECX, 0x2BADB002
	cmp ECX, EAX
	jne HandleNoMultiboot

	mov dword [MultibootInfo_Structure], EBX
	add dword EBX, 0x4
	mov dword EAX, [EBX]
	mov dword [MultibootInfo_Memory_Low], EAX
	add dword EBX, 0x4
	mov dword EAX, [EBX]
	mov dword [MultibootInfo_Memory_High], EAX
	; END - Multiboot Info

	; BEGIN - Set Screen Colour
	mov dword EBX, DISP_ADDR 	; Display Memory address
	mov dword ECX, SCR_SIZ
	.ColourOutput:
	mov byte [EBX], 0
	mov byte [EBX+1], AL
	add EBX, 2
	loop .ColourOutput
	; END - Set Screen Colour

	; BEGIN - Switch to protected mode
	mov dword EAX, CR0
	or EAX, 1
	mov dword CR0, EAX
	; END - Switch to protected mode

	; BEGIN - Set Screen Colour
	mov dword EBX, DISP_ADDR 	; Display Memory address
	mov dword ECX, SCR_SIZ
	.ColourOutput2:
	mov byte [EBX], 0
	mov byte [EBX+1], AL
	add EBX, 2
	loop .ColourOutput2
	; END - Set Screen Colour

	; BEGIN - Set stack pointer
	mov dword ESP, Kernel_Stack_Start
	; END - Set stack pointer

	; BEGIN - Set Screen Colour
	mov dword EBX, DISP_ADDR 	; Display Memory address
	mov dword ECX, SCR_SIZ
	.ColourOutput3:
	mov byte [EBX], 0
	mov byte [EBX+1], AL
	add EBX, 2
	loop .ColourOutput3
	; END - Set Screen Colour

	; BEGIN - Tell CPU about GDT
	mov dword [GDT_Pointer + 2], GDT_Contents
	mov dword EAX, GDT_Pointer
	lgdt [EAX]
	; Set data segments
	mov dword EAX, 0x10
	mov word DS, EAX
	mov word ES, EAX
	mov word FS, EAX
	mov word GS, EAX
	mov word SS, EAX
	; Force reload of code segment
	jmp 8:Boot_FlushCsGDT
Boot_FlushCsGDT:
	; END - Tell CPU about GDT

	; BEGIN - Set Screen Colour
	mov dword EBX, DISP_ADDR 	; Display Memory address
	mov dword ECX, SCR_SIZ
	.ColourOutput4:
	mov byte [EBX], 0
	mov byte [EBX+1], AL
	add EBX, 2
	loop .ColourOutput4
	; END - Set Screen Colour

	call main ; call c main function

	jmp Halt

HandleNoMultiboot:
	; BEGIN - Set Screen Colour
	mov dword EBX, DISP_ADDR 	; Display Memory address
	mov dword ECX, SCR_SIZ
	.ColourOutput:
	mov byte [EBX], 0
	mov byte [EBX+1], AL
	add EBX, 2
	loop .ColourOutput
	; END - Set Screen Colour

Halt:
	cli			; Stop maskable interrupts
	hlt			; Halt the processor
	jmp Halt	; If non-maskable interrupt occurs, re-halt
