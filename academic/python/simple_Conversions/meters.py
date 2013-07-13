#Nianzu Wang
#Email: wangn89@gmail.com

#meters.py: This prompts the user for the amount of inches they want to convert to meters.

#prompts user for input
inch = raw_input("How many inches?")

#calculations
meter = float(inch) / float(39.3700787)

#output
print str(inch) + " inches equals " + '%.3f' % float(meter) + " meters."
