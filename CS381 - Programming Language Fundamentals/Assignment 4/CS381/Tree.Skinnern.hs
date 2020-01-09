--

-- Nicholas Skinner

-- CS 381 

-- 1/20/18

-- Assignment 1

--



module Tree where


--
-- * Part 1: Binary trees
--

-- | Integer-labeled binary trees.
data Tree = Node Int Tree Tree   -- ^ Internal nodes
          | Leaf Int             -- ^ Leaf nodes
  deriving (Eq,Show)


-- | An example binary tree, which will be used in tests.
t1 :: Tree
t1 = Node 1 (Node 2 (Node 3 (Leaf 4) (Leaf 5))
                    (Leaf 6))
            (Node 7 (Leaf 8) (Leaf 9))

-- | Another example binary tree, used in tests.
t2 :: Tree
t2 = Node 6 (Node 2 (Leaf 1) (Node 4 (Leaf 3) (Leaf 5)))
            (Node 8 (Leaf 7) (Leaf 9))


-- | The integer at the left-most node of a binary tree.
--


--   >>> leftmost (Leaf 3)
--   3
--
--   >>> leftmost (Node 5 (Leaf 6) (Leaf 7))
--   6
--
--   >>> leftmost t1
--   4
--
--   >>> leftmost t2
--   1
--
--  leftmost will be tree to int, searching through the leaf and node
leftmost :: Tree -> Int --tree to int
leftmost (Leaf i)     = i --looking at the leafs now
leftmost (Node _ l _) = leftmost l --the leftmost leaf is what we are interested in, and we will use the nodes first leaf to find it


-- | The integer at the right-most node of a binary tree.
--
--   >>> rightmost (Leaf 3)
--   3
--
--   >>> rightmost (Node 5 (Leaf 6) (Leaf 7))
--   7
--
--   >>> rightmost t1
--   9
--
--   >>> rightmost t2
--   9
--
--  rightmost will be tree to int, searching through the leaf and node
rightmost :: Tree -> Int --tree to int
rightmost (Leaf i)     = i --looking at the leafs now
rightmost (Node _ _ r) = rightmost r --the rightmost leaf is what we need, we will use the end portion of the node to find the rightmost value


-- | Get the maximum integer from a binary tree.
--
--   >>> maxInt (Leaf 3)
--   3
--
--   >>> maxInt (Node 5 (Leaf 4) (Leaf 2))
--   5
--
--   >>> maxInt (Node 5 (Leaf 7) (Leaf 2))
--   7
--
--   >>> maxInt t1
--   9
--
--   >>> maxInt t2
--   9
--

-- to do this, we will want to do a bit of searching through the tree's int values, so to begin we will tree -> int
maxInt :: Tree -> Int --so to begin we will tree -> int
maxInt (Leaf i) = i --start looking at leafs
maxInt (Node val l r) = max3way (maxInt l) (val) (maxInt r) --here we will be looking through the tree, to find the maxints of all the leafs
max3way :: Int -> Int -> Int -> Int --max list to grab all max ints
max3way a b c = max (a) (max b c) --compare to see what is the largest

-- | Get the minimum integer from a binary tree.
--
--   >>> minInt (Leaf 3)
--   3
--
--   >>> minInt (Node 2 (Leaf 5) (Leaf 4))
--   2
--
--   >>> minInt (Node 5 (Leaf 4) (Leaf 7))
--   4
--
--   >>> minInt t1
--   1
--
--   >>> minInt t2
--   1
--


minInt :: Tree -> Int -- we need our tree and an int for this
minInt (Leaf i) = i --we want to create our leaf variable
minInt (Node val l r) = min3way (minInt l) (val) (minInt r) --here we will look through the tree to search for the minimum number
min3way :: Int -> Int -> Int -> Int --max list to grab all min ints
min3way a b c = min (a) (min b c) --determine min

-- | Get the sum of the integers in a binary tree.
--
--   >>> sumInts (Leaf 3)
--   3
--
--   >>> sumInts (Node 2 (Leaf 5) (Leaf 4))
--   11
--
--   >>> sumInts t1
--   45
--
--   >>> sumInts (Node 10 t1 t2)
--   100
--

--sum of all intigers on the binary tree
sumInts :: Tree -> Int --using types tree and int
sumInts (Leaf i) = i --create our leaf
sumInts (Node val l r) = val + (sumInts l) + (sumInts r) -- call our sumints to get all left, values, all right values, and node then add together


-- | The list of integers encountered by a pre-order traversal of the tree.
--


--   >>> preorder (Leaf 3)
--   [3]
--
--   >>> preorder (Node 5 (Leaf 6) (Leaf 7))
--   [5,6,7]
--
--   >>> preorder t1
--   [1,2,3,4,5,6,7,8,9]
--
--   >>> preorder t2
--   [6,2,1,4,3,5,8,7,9]
--

preorder :: Tree -> [Int] --we want to get this from highest level to lowest level left to right, meaning t1 will be 1,2,3,4...
preorder (Leaf i) = [i] --create leaf array
preorder (Node val l r) = val:(preorder l) ++ (preorder r) -- grab first node, and work way down



-- | The list of integers encountered by an in-order traversal of the tree.
--
--   >>> inorder (Leaf 3)
--   [3]
--
--   >>> inorder (Node 5 (Leaf 6) (Leaf 7))
--   [6,5,7]
--
--   >>> inorder t1
--   [4,3,5,2,6,1,8,7,9]
--
--   >>> inorder t2
--   [1,2,3,4,5,6,7,8,9]
--

inorder :: Tree -> [Int] --using tree and an array
inorder (Leaf i) = [i] --create leaf
inorder (Node val l r) = (inorder l) ++ [val] ++ (inorder r) -- go through our tree, and grab leafs and nodes from leftmost to rightmost


-- | Check whether a binary tree is a binary search tree.
--
--   >>> isBST (Leaf 3)
--   True
--
--   >>> isBST (Node 5 (Leaf 6) (Leaf 7))
--   False
--
--   >>> isBST t1
--   False
--
--   >>> isBST t2
--   True
--


--check if the tree is a binary search tree
--bst = left nodes have values less than parent, right nodes have values greater
--bt = doesn't care about bst stuff
isBST :: Tree -> Bool
isBST (Leaf i) = True
isBST (Node val l r) =  (val > (valueBST l)) && (isBST l) && (val < (valueBST r)) && (isBST r) 
valueBST :: Tree -> Int -- making a method to grab a value from the tree to compare
valueBST (Leaf i) = i --creating leaf
valueBST (Node val l r) = val --getting value to be used in comparison


-- | Check whether a number is contained in a binary search tree.
--   (You may assume that the given tree is a binary search tree.)
--
--   >>> inBST 2 (Node 5 (Leaf 2) (Leaf 7))
--   True
--
--   >>> inBST 3 (Node 5 (Leaf 2) (Leaf 7))
--   False
--
--   >>> inBST 4 t2
--   True
--
--   >>> inBST 10 t2
--   False
--

--in binary search tree
inBST :: Int -> Tree -> Bool --using types int/tree/bool
inBST num (Leaf i) = num == i --get our leaf
inBST num (Node val l r) = any (== num) (inorder (Node val l r)) --do our search through left/right nodes, seeing if any are equal to the val given. if it is found return true