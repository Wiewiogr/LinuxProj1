from drzewo import *
import unittest

class TestTreeMethods(unittest.TestCase):
    def test_init(self):
        tc = Tree(5)
        self.assertEqual(tc.tree,[[5],[]])

    def test_addLeafToRoot(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        self.assertEqual(tc.tree,[[5],[[3]],[[]]])

    def test_addTwoLeavesToRoot(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(5,2)
        self.assertEqual(tc.tree,[[5],[[3,2]],[[],[]]])

    def test_addThreeLeavesToRoot(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(5,2)
        tc.addLeaf(5,1)
        self.assertEqual(tc.tree,[[5],[[3,2,1]],[[],[],[]]])

    def test_addLeafToLeaf(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(3,1)
        self.assertEqual(tc.tree,[[5],[[3]],[[1]],[[]]])

    def test_addTwoLeavesToLeaf(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(3,1)
        tc.addLeaf(3,2)
        self.assertEqual(tc.tree,[[5],[[3]],[[1,2]],[[],[]]])

    def test_addLeavesToTwoDifferentLeaves(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(5,4)
        tc.addLeaf(3,1)
        tc.addLeaf(4,2)
        self.assertEqual(tc.tree,[[5],[[3,4]],[[1],[2]],[[],[]]])

    def test_addLeavesToTwoDifferentLeavesThenToSecondOnFirstLevel(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(5,4)
        tc.addLeaf(3,1)
        tc.addLeaf(4,2)
        tc.addLeaf(2,6)
        self.assertEqual(tc.tree,[[5],[[3,4]],[[1],[2]],[[],[6]],[[]]])

    def test_addTwoLeavesToTwoDifferentLeaves(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(5,4)
        tc.addLeaf(3,1)
        tc.addLeaf(3,2)
        tc.addLeaf(4,6)
        tc.addLeaf(4,7)
        self.assertEqual(tc.tree,[[5],[[3,4]],[[1,2],[6,7]],[[],[],[],[]]])

    def test_addTwoLeavesToTwoDifferentLeavesMixedOrder(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(5,4)
        tc.addLeaf(3,1)
        tc.addLeaf(4,6)
        tc.addLeaf(3,2)
        tc.addLeaf(4,7)
        self.assertEqual(tc.tree,[[5],[[3,4]],[[1,2],[6,7]],[[],[],[],[]]])

    def test_addLeafToLeafThatDoesntExistShouldRaiseExcept(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        with self.assertRaises(ValueError):
            tc.addLeaf(7,1)

    def test_addLeavesToTwoDifferentLeavesThenToRoot(self):
        tc = Tree(5)
        tc.addLeaf(5,3)
        tc.addLeaf(5,4)
        tc.addLeaf(3,1)
        tc.addLeaf(4,2)
        tc.addLeaf(5,9)
        self.assertEqual(tc.tree,[[5],[[3,4,9]],[[1],[2],[]],[[],[]]])

if __name__ == '__main__':
    unittest.main(verbosity=2)
