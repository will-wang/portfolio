#Name: Nianzu Wang
#Email: wangn89@gmail.com

#phonebook_pythonian.py: some fun with phonebooks and stringplay


def findNumber(phoneBook):
    name = raw_input("Whose number would you like to get? ")
    if phoneBook.has_key(name):
        print name + "'s number is " + phoneBook[name]
    else:
        print name + " is not in the phonebook sorry."

def getNumbers(phoneBook):
    findNumber(phoneBook)
    ans = raw_input("Would you like to get another (y/n)? ")
    if ans == "y":
        getNumbers(phoneBook)
    elif ans == "n":
        return
    else:
        print "Not valid entry"
        getNumbers(phoneBook)


Pythonian = {'a':'z','c':'x','b':'y','e':'v','d':'w','g':'t','f':'u','i':'r',\
             'h':'s','k':'p','j':'q','m':'n','l':'o','o':'l','n':'m','q':'j',\
             'p':'k','s':'h','r':'i','u':'f','t':'g','w':'d','v':'e','y':'b',\
             'x':'c','z':'a', ' ':' '}

def translator(sentence):
    translated = ""
    for char in sentence:
        if Pythonian.has_key(char):
            translated += Pythonian[char]
        else:
            char = char.lower()
            if Pythonian.has_key(char):
                newchar = Pythonian[char]
                translated += newchar.upper()
    return translated


def decode(code):
    codes = {'012':'America','034':'Sweden','021':'Mexico','056':'Georgia',\
             '098':'Canada','043':'Russia','025':'Czech Republic',\
             '090':'Israel','084':'Japan','011':'China'}
    return codes[code]

def formatter(numbers):
    code = numbers[:3]
    country = decode(code)
    return country + ": " + numbers[3:6] + "-" + numbers[6:9] + "-" + numbers[9:13]


