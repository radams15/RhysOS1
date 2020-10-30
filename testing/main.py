
def pow(num, power):
    out = num
    for i in range(0, power):
        out *= num
    return out

num = 987654321
size=0

num_temp = num
while True:
    num_temp = num_temp//10
    size+=1
    if num_temp == 0:
        break

power = int(pow(10, size-1))

while True:
    p = num % power
    #num = num//power

    #c = i^0b00110000
    #print(chr(c))

    if power > 10:
        i = p // (power // 10)
        print(i)
    else:
        print(p)
        break

    power //= 10

    if power == 0:
        break