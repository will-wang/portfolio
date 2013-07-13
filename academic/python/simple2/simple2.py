#Nianzu Wang
#Email: wangn89@gmail.com

#simple2.py: some simple math functions

def multiply(num1,num2):
    sum = 0
    while num1 > 0:
        sum = sum + num2
        num1 = num1 - 1
    return sum
    
def summation(x):
    count = 0
    total = 0
    while count <= x:
        total = total + count
        count = count + 1
    return total

def digitSum(number):
    count = 0
    while number > 0:
        remainder = number%10
        count = count + remainder
        number/=10
    return count
