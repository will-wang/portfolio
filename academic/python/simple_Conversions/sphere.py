#Nianzu Wang
#Email: wangn89@gmail.com

#sphere.py: This prompts the user for the radius of the sphere they want to calculate the volume of.

#importing the math library
import math

#prompting for user input
radius = raw_input("Please enter the radius of the sphere:")

#converting radius to float
radius = float(radius)
volume =(radius)*(radius)*(radius) * 4.0/3.0 * math.pi

#output
print "The volume of the sphere: " '%.2f' % float(volume)
