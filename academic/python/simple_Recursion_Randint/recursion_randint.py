#Nianzu Wang
#Email: wangn89@gmail.com

#recursion_randint.py: demonstrates the use of recursion


#calculates the "double factorial" of a number; the number must be non-negative and even
def doubleFactorial(num):

    #check edge case for when number = 0, return 1 if so
    if num == 0:
        return 1
    
    #modulus (%) is used to determine if the input is an even number
    elif num > 0 and num%2 == 0:
        
        #recursive call
        return num * doubleFactorial(num-2)

    #else edge case when number provided is either a negative or odd number; output feedback
    else:
        return 'That was either a negative or odd number. Please enter a positive, even number.'



#calculates the product of two numbers
def multiply(num1,num2):

    #checking edge case when either numbers are 0; returns 0
    if num1 == 0 or num2 == 0:
        return 0

    #recursive call performing the multiplication
    else:
        return num1 + multiply(num1, num2 - 1)
  
    

#demonstrates a custom error message using try/except
def gimmeNumber():

    #prompts user for input as a number
    num = raw_input("Gimme a number! ")

    #try block
    try:

        #converts the num to an int
        num = int(num)

        #returns the sum of the number and 5
        return num + 5

    #except block; defines the type of exception
    except ValueError:

        #defines the feedback for that exception
        print "A number was not entered!"



#the random module and randint is necessary for the random roll of dice or selection of cards.
from random import *

#demonstrates using randint to simulate a rolling of a 7-sided die
def rollDie():
    d = randint(1, 7)
    d = str(d)
    print "You rolled " + d
    return go()

#demonstrates rolling two 7-sided dice and outputting the sum
def rollDice():
    a = randint(1, 7)
    b = randint(1, 7)
    a = int(a)
    b = int(b)
    tot = a + b
    tot = str(tot)
    print "You rolled " + tot
    return go()

#demonstrates using randint to simulate picking of cards
def pickCard():
    c = randint(1, 13)
    if c == 1:
        print "You picked an Ace"
    elif c == 11:
        print "You picked a Jack"
    elif c == 12:
        print "You picked a Queen"
    elif c == 13:
        print "You picked a King"
    else:
        c = str(c)
        print "You picked a " + c
    go()

#outputted menu for games previously defined
def menu():
    print """
    What can I do for you?
    1.  Roll a die
    2.  Roll two dice!
    3.  Pick a card
    4.  Nothing, wish to quit
    """
    return int(raw_input("choice? "))
    
#work done after user makes selection from above menu()
def go():
    choice = menu()
    if choice == 1:
        rollDie()
        go()
    elif choice == 2:
        rollDice()
        go()
    elif choice == 3:
        pickCard()
        go()
    else:
        return "Thanks for playing!"
