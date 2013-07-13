#Nianzu Wang
#Email: wangn89@gmail.com

#simple1.py: demonstrastes some simple calculations, functions, and the use of main().


#calculates the average miles per minute of a runner.
def avgMiles(miles, time):

    #calculate the average using float for more accuracy
    avg = float(time) / float(miles)

    #DEBUG: print "You ran " + avg + " miles per minute."

    #return average for main() to use
    return avg


#calculates the miles per hour of the runner.
def mph(miles, time):

    #convert the time to hours
    hour = float(time) / 60.00

    #calculte the speed in miles per hour
    speed = float(miles) / float(hour)

    #return speed for main() to use
    return float(speed)


#calculates the calories burned of the runner using 100 calories per mile.
def caloriesBurned(miles):

    #calculate the total amount burned
    burn = float(miles) * 100

    #return the total for main() to use
    return burn


#main(): prompts user for input, calculates and outputs text.
def main():

    #prompts user for miles and time in minutes of run
    miles = raw_input("How many miles did you run?")
    time = raw_input("How long was your run? (in minutes)")

    #calling previously defined functions to do work and fill in blanks
    blankA = mph(miles, time)
    blankB = caloriesBurned(miles)
    bonus = avgMiles(miles, time)

    #output
    print "You run at " + str(blankA) + " miles per hour!"
    print "And you burned " + str(blankB) + " calories."

    #if/else statement to provide feedback based on speed
    if blankA > 15:
        print "You run as fast as a car! Vroom vroom!"
    elif 15 > blankA > 6:
        print "What a speed demon you are!"
    else:
        print "Pump it up, champ."

    #extra output
    print "You also run a mile in about " + str(bonus) + " minutes."



#outputs a number of stars; uses double quotes      
def printStars(num):
    print num * "*"


#returns a number of stars for something else to use; uses single quotes
def returnStars(num):
    return num * '*'



#demonstrates printing the addition of two floats
def printAdd(a,b):
    print float(a) + float(b)


#demonstrates returning the addition of two floats
def returnAdd(a,b):
    return float(a) + float(b)


#demonstrates the difference between printing and returning the addition of two floats
def useAdd(a,b):
    print "This is printAdd's output printed:"
    print printAdd(a,b)
    print "This is returnAdd's output printed:"
    print returnAdd(a,b)
    print "This is printAdd's output without print:"
    printAdd(a,b)
    print "This is returnAdd's output without print:"
    returnAdd(a,b)



#demonstrates the use of len() and the use of (int)*"str"; use: printName("name")
def printName(name):

    #defines x as the length of the name
    x = len(name)

    #outputs x amount of stars, then the name, then x amount of stars
    print x * "*"
    print name
    print x * "*"
