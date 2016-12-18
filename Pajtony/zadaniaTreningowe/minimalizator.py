import itertools

def minimalizator(fun,funArg):
    minValue = None
    iterations = []
    for curPermutation in itertools.permutations(funArg):
        result = fun(curPermutation[0],curPermutation[1],curPermutation[2])
        print "fun(",curPermutation,") =", result
        if minValue == None or result < minValue:
            iterations = [curPermutation]
            minValue = result
        elif minValue == result:
            iterations.append(curPermutation)
    return iterations


F = lambda a,b,c : a*b+c

print minimalizator(F,(1,2,3))


