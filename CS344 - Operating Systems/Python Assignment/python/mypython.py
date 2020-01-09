import random
import string

#open files with write permissions
randFile1 = open("rand1", 'w')
randFile2 = open("rand2", 'w')
randFile3 = open("rand3", 'w')

files = [randFile1, randFile2, randFile3]

for file in files:
    #generate the strings that will be used with our files
    rand = ''.join(random.choice(string.ascii_lowercase) for n in xrange(10))

    #write the created string to our files
    file.write(rand)
    file.write('\n') #create a new line
    file.close()

#open files with read permissions
randFile1 = open("rand1", 'r')
randFile2 = open("rand2", 'r')
randFile3 = open("rand3", 'r')

files = [randFile1, randFile2, randFile3]

#print the letters into the files
# 10 letters per line
for file in files:
    line = file.read(10) 
    print line

# generate random numbers
from random import randint

# random int between 1 and 42 inclusive
randNum1 = randint(1,42)
randNum2 = randint(1,42)

# print random numbers
print randNum1
print randNum2

# print product of random numbers
product = randNum1 * randNum2
print product 