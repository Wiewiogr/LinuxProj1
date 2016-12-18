import itertools

def minimalizator(fun,funArg):
    minValue = None
    iterations = []
    for currentIteration in itertools.permutations(funArg):
        result = fun(currentIteration[0],currentIteration[1],currentIteration[2])
        print "fun(",currentIteration,") =", result
        if minValue == None or result < minValue:
            iterations = [currentIteration]
            minValue = result
        elif minValue == result:
            iterations.append(currentIteration)
    return iterations


F = lambda a,b,c : a*b+c

print minimalizator(F,(1,2,3))


