#Nianzu Wang
#Email: wangn89@gmail.com

#ospath_prime.py: some fun things with isdir, isfile, join, and prime numbers

import os

from os.path import join, isfile, isdir


def compareNum(path):
    if os.path.isdir(path) == True:
        names = os.listdir(path)
        file_count = 0
        dir_count = 0
        for name in names:
            longname = os.path.join(path, name)
            if isfile(longname):
                file_count += 1
            elif isdir(longname):
                dir_count += 1
        if dir_count > file_count:
            print "There are " + str(dir_count) + " folders and " + str(file_count) + " files in the folder " + path
            print "There are more folders than files."
        elif file_count > dir_count:
            print "There are " + str(dir_count) + " folders and " + str(file_count) + " files in the folder " + path
            print "There are more files than folders."
        else:
            print "There are " + str(dir_count) + " folders and " + str(file_count) + " files in the folder " + path
            print "There are an equal number of files and folders."
    else:
        print "Invalid path."


def countFiles(path):
    if os.path.isdir(path) == True:
        names = os.listdir(path)
        jpg_count = 0
        txt_count = 0
        html_count = 0
        for name in names:
            longname = os.path.join(path, name)
            name = name.lower()
            if isfile(longname) and name.endswith(".jpg"):
                jpg_count += 1
            elif isfile(longname) and name.endswith(".txt"):
                txt_count += 1
            elif isfile(longname) and name.endswith(".html"):
                html_count += 1
        print ".jpg: " + str(jpg_count)
        print ".txt: " + str(txt_count)
        print ".html: " + str(html_count)
    else:
        print "Invalid path."


def isPrime(prime):
    for num in range(2, prime):
        if prime % num != 0:
            return True
        else:
            return False

#use: maxPrime([number1,number2,etc])
def maxPrime(numbers):
    prime = []
    count = 0
    for value in numbers:
        if isPrime(value) == True:
            prime = prime + [str(value)]
            count += 1
    if count == 0:
            print "No prime numbers were found."
    else:
        prime.sort()
        print prime[-1]


def countByType(path):
    if os.path.isdir(path) == True:
        names = os.listdir(path)
        music_count = 0
        image_count = 0
        video_count = 0
        document_count = 0
        python_count = 0
        count = 0
        for name in names:
            longname = os.path.join(path, name)
            name = name.lower()
            if isfile(longname):
                if name.endswith(".jpg"):
                    image_count += 1
                elif name.endswith(".mp3"):
                    music_count += 1
                elif name.endswith(".avi"):
                    video_count += 1
                elif name.endswith(".doc"):
                    document_count += 1
                elif name.endswith(".py"):
                    python_count += 1
                else:
                    count = count
            else:
                count = count
        print "Music: \t \t" + str(music_count)
        print "Images: \t" + str(image_count)
        print "Videos: \t" + str(video_count)
        print "Documents: \t" + str(document_count)
        print "Python: \t" + str(python_count)
    else:
        print "Invalid path."
        
