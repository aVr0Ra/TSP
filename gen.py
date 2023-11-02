import random

n = 10#random.randint(1 , 10)

file = open("input.in" , "w")
file.write(f"{n}\n")

for i in range(0 , n):
    for j in range(0 , n):
        if i == j:
            file.write("0 ")
        else:
            now = random.randint(0 , 10000)
            file.write(f"{now} ")
    
    file.write("\n")

file.close()
