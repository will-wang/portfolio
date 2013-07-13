#Nianzu Wang
#Email: wangn89@gmail.com

#kilometers/py: Prompts user for the number of miles they want to convert to kilometers.

#prompt user for input
miles = raw_input('How many miles?')

#calculations
kilo = float(miles) * 1.609344

#output
print "Number of kilometers: " + '%.1f' % float(kilo)
