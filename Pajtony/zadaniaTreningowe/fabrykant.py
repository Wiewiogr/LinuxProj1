def fabrykant(F, L):
    def funkcja(args):
        res = None
        for i in L:
            if res == None:
                res = args[i]
            else:
                res = F(res,args[i])
        return res
    return funkcja

S = lambda x, y : x+y
t = fabrykant(S,[1,3,5])

print t(range(10))
print t(range(10,2,-1))

