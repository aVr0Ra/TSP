import os,sys,random,subprocess

#for cnt in range(0 , 10000):
    #os.system("python3 gen.py")
os.system("./brutal")
os.system("./TSP")

dif = "diff brutal.out dp.out"
result = subprocess.getoutput(dif)

if result != "":
    # print(result)
    os.system("cat input.in")

