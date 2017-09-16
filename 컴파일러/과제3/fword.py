# fileword3.py
import cStringIO

likeFile = cStringIO.StringIO(text)
 
def word_list(fp): 
    fileLines = fp.readlines()
    word = []
    for line in fileLines:
       word += line.split()
    return word

print word_list(likeFile) 
