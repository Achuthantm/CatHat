import sys, os, time, shutil
## First Argument is number of times you want to run the code 
os.system('g++-15 gen.cpp -o gen \n g++-15 main1.cpp -o main1 \n g++-15 brute.cpp -o brute \n ')
print("Compiled all files")
counter = 0
while(True):
        counter = counter + 1
        os.system(' ./gen > input.txt \n ./main1 < input.txt > out2 \n ./brute < input.txt > out1 \n ')
        data1 = ''
        data2 = ''
        with open('out1', 'r') as file:
                data1 = file.read()
        with open('out2', 'r') as file:
                data2 = file.read()
        if data1 == data2:
                print("Passes Testcase", counter)
        else:
                break
        if(counter > (int)(sys.argv[1])):
                break