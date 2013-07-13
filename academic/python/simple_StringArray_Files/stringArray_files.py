#Nianzu Wang
#email: wangn89@gmail.com

#stringArray_files.py: demonstrates some functions involving text and files in directories



#demonstrates what a word is in pig latin; use: pigLatin("word")
def pigLatin(word):
    text = word

    #checks whether the first letter of the word is a vowel
    while text[0] == 'a' or text[0] == 'A' or text[0] == 'e' or text[0] == 'E' or text[0] == 'i' or text[0] == 'I' or text[0] == 'o' or text[0] == 'O' or text[0] == 'u' or text[0] == 'U':

        #returns that word with "ay" appended to it if so
        return word + 'ay'

    #returns the word with the first and last letters swapped and appended with "ay" if else
    return text[1:] + text[0] + 'ay'



#demonstrates separating a word, capitalizing the first letter, and lowercasing the rest; use: myCapitalize("word")
def myCapitalize(word):
    text = word

    #separating the parts
    first = text[0]
    rest = text[1:]

    #returns the result, using upper() and lower()
    return first.upper() + rest.lower()



#demonstrates if a string starts with another; ; use: myStartsWith("word1","word2")
def myStartsWith(word1,word2):

    #defining x as the length of word2 (the string to match)
    x = len(word2)

    #check the first x characters of word1; return either true or false
    if word2 == word1[0:x]:
        return True
    else:
        return False



#demonstrates the use of for loop, isfile(), and endswith() to list the mps files in a given directory; use: printMP3("path")
import os
from os.path import isdir, isfile, join

def printMP3(path):
    names = os.listdir(path)
    for name in names:
        longname = join(path, name)
        if isfile(longname) and longname.endswith(".mp3"):
            print longname
