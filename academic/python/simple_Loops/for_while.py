#Nianzu Wang
#Email: wangn89@gmail.com

#for_while.py: demonstrates some fun things with for and while loops

def starsFor(x):
    array = range(x, 0, -1)
    array2 = range(1, x)
    for num in array2:
        print "*" * num
    for num in array:
        print "*" * num

def starsWhile(n):
    a = 1
    while a < n:
        print "*" * a
        a += 1        
    while n > 0:
        print "*" * n
        n -= 1
    return

def countdown(x):
    array = range(x, -1, -1)
    for num in array:
        if num == 0:
            print "Blastoff!!!"
        else:
            print num

def parade(string):
    lineUp = list(string)
    print """Welcome to the Dragon*Con Parade!
    The marching order is as follows:"""
    for num in lineUp:
        if num == "1":
            print num + " - Klingons"
        elif num == "2":
            print num + " - Storm Troopers"
        elif num == "3":
            print num + " - SGC Officers"
        elif num == "4":
            print num + " - Superheroes"
        elif num == "5":
            print num + " - Elves"
        elif num == "6":
            print num + " - Video Game Characters"
        else:
            print num + " - Not in Parade"

def walkOfFame():
    celeb = input("""We're off to see celebrities!
How many guests would you like to see?""")
    if celeb == 0:
        return "Maybe you should try gaming..."
    nums = range(celeb, 0, -1)
    array = " "
    for num in nums:
        name = raw_input("Please enter the guest's name.")
        if len(name) <= 6:
            print name + " ...Who?"
            array += (" " + name)
        elif len(name) <= 9:
            print name + " Hey, I've seen them in that show!"
            array += (" " + name)
        elif len(name) <= 12:
            print name + " Ooh, getting to the big time!"
            array += (" " + name)
        else:
            print name + " Wow! They are super famous. Definitely worth the autograph."
            array += (" " + name)
    print
    print "Get those autograph books ready, you get to see: "
    print array
