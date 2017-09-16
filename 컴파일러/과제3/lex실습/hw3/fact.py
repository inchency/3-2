# factorial.py 

def factorial(theNumber):
    result = 1L
    while theNumber > 0: 
       result = result * theNumber
       theNumber = theNumber-1
    return result

print factorial(4)
