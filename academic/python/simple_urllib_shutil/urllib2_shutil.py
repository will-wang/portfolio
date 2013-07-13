#Nianzu Wang
#Email: wangn89@gmail.com

#urllib2_shutil.py: fun with urllib2 and shutil

import urllib2
import os
import shutil
from os.path import join, isfile

def getHumidity():
    url = "http://www.weather.com/outlook/travel/businesstraveler/local/30309?lswe=30309&lwsa=Weather36HourBusinessTravelerCommand&from=whatwhere"
    for line in urllib2.urlopen(url):
        if "Humidity" in line and "%" in line:
            humidity = line
    return "The humidity is: " + humidity[90:93]


def avgNums(location):
    file = open(location)
    nums = 0
    linenum = 0
    for line in file.readlines():
        nums += float(line)
        linenum += 1
    return "The average of the numbers in the file is " + str(nums / linenum)


def makeImageFolder(source):
    names = os.listdir(source)
    os.mkdir("C:/Images")
    destinationJpeg = "C:/Images/jpeg"
    os.mkdir(destinationJpeg)
    destinationPng = "C:/Images/png"
    os.mkdir(destinationPng)
    destinationGif = "C:/Images/gif"
    os.mkdir(destinationGif)
    for name in names:
        longname = os.path.join(source,name)
        if isfile(longname) and name.endswith(".jpeg" or ".JPEG"):
            shutil.copy(longname, destinationJpeg)
        elif isfile(longname) and name.endswith(".png" or ".PNG"):
            shutil.copy(longname, destinationPng)
        elif isfile(longname) and name.endswith(".gif" or ".GIF"):
            shutil.copy(longname, destinationGif)


def makePicAlbum(path):
    album = "album.html"
    html = "<html>"
    html += getImages(path)
    html += "</html>"
    htmlFile = open(os.path.join(path,album), "w")
    htmlFile.write(html)
    htmlFile.close


def getImages(path):
    html = ""
    names = os.listdir(path)
    imgcount = 0
    for name in names:
        longname = os.path.join(path,name)
        if isfile(longname) and name.endswith(".jpg" or ".JPG"):
            html += '''<img src = "'''+ longname + '''" height = "100" width = "100">'''
            imgcount += 1
            if imgcount > 4:
                html += "<br/>"
                imgcount = 0
        if os.path.isdir(longname):
            getImages(longname)
    return html
