class Tree(object):
    def __init__(self,root):
        self.tree = [[root],[]]

    def addLeafToRoot(self,val):
        if len(self.tree[1]) == 0:
            self.tree.append([[]])
            self.tree[1].append([val])
        else:
            self.tree[2].append([])
            self.tree[1][0].append(val)

    def addLeafToLeaf(self,pos,val):
        if len(self.tree[pos['i']+1][0]) == 0:
            self.tree.append([[]])
            self.tree[pos['i']+1][pos['j']+pos['k']].append(val)
        else:
            self.tree[pos['i']+2].append([])
            self.tree[pos['i']+1][pos['j']+pos['k']].append(val)

    def findPosition(self, par):
        for _i in xrange(1,len(self.tree)-1):
            for _j in xrange(len(self.tree[_i])):
                for _k in xrange(len(self.tree[_i][_j])):
                    if self.tree[_i][_j][_k] == par:
                        return {'i':_i,'j':_j,'k':_k}
        else:
            raise ValueError

    def addLeaf(self,par,val):
        if par == self.tree[0][0]:
            return self.addLeafToRoot(val)
        else:
            pos = self.findPosition(par)
            return self.addLeafToLeaf(pos,val)

    def show(self):
        print self.tree


if __name__ == "__main__":
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(3,1)
