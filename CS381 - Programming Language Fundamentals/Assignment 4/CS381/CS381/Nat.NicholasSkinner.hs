-------------------------------------------------
-- Nicholas Skinner

-- CS 381 

-- 1/20/18

-- Assignment 1

-------------------------------------------------
module Nat where

import Prelude hiding (Enum(..), sum)


--
-- * Part 2: Natural numbers
--

-- | The natural numbers.
data Nat = Zero
         | Succ Nat
  deriving (Eq,Show)

-- | The number 1.
one :: Nat
one = Succ Zero

-- | The number 2.
two :: Nat
two = Succ one

-- | The number 3.
three :: Nat
three = Succ two

-- | The number 4.
four :: Nat
four = Succ three

-- | The predecessor of a natural number.
--

--   >>> pred Zero
--   Zero
--
--   >>> pred three
--   Succ (Succ Zero)
--
pred :: Nat -> Nat
pred Zero = Zero
pred (Succ x) = x
-- | True if the given value is zero.
--
--   >>> isZero Zero
--   True
--
--   >>> isZero two
--   False
--
isZero :: Nat -> Bool
isZero Zero = True
isZero _ = False

-- | Convert a natural number to an integer.
--
--   >>> toInt Zero
--   0
--
--   >>> toInt three
--   3
--
toInt :: Nat -> Int
toInt Zero = 0
toInt x = (toInt (pred x)) + 1

-- | Add two natural numbers.
--
--   >>> add one two
--   Succ (Succ (Succ Zero))
--
--   >>> add Zero one == one
--   True
--
--   >>> add two two == four
--   True
--
--   >>> add two three == add three two
--   True
--

-- we want to add two nats into one supernat
add :: Nat -> Nat -> Nat --nat nat, and end nat
add Zero x = x
add x Zero = x
add x y = add (pred x) (Succ y)

-- | Subtract the second natural number from the first. Return zero
--   if the second number is bigger.
--
--   >>> sub two one
--   Succ Zero
--
--   >>> sub three one
--   Succ (Succ Zero)
--
--   >>> sub one one
--   Zero
--
--   >>> sub one three
--   Zero
--
-- we want to subtract two nats, and get the result
sub :: Nat -> Nat -> Nat --nat nat, and end nat
sub Zero x = Zero
sub x Zero = x
sub x y = sub (pred x) (pred y)


-- | Is the left value greater than the right?
--
--   >>> gt one two
--   False
--
--   >>> gt two one
--   True
--
--   >>> gt two two
--   False
--

--left value greater than, 
gt :: Nat -> Nat -> Bool --we need our two nat inputs, and then our boolean output
gt x y = (toInt x) > (toInt y)


-- | Multiply two natural numbers.
--
--   >>> mult two Zero
--   Zero
--
--   >>> mult Zero three
--   Zero
--
--   >>> toInt (mult two three)
--   6
--
--   >>> toInt (mult three three)
--   9
--

--multiply two numbers
mult :: Nat -> Nat -> Nat -- we want our first nat, our second nat, and our end nat
mult x Zero = Zero -- zero case
mult Zero x = Zero -- zero case
--mult x y = nums !! ((toInt x) * (toInt y))
mult x y = sum(take (toInt x) (repeat y))


-- | Compute the sum of a list of natural numbers.
--
--   >>> sum []
--   Zero
--
--   >>> sum [one,Zero,two]
--   Succ (Succ (Succ Zero))
--
--   >>> toInt (sum [one,two,three])
--   6
--

-- we want to get the total sum from a list of numbers
sum :: [Nat] -> Nat --our natural number list, and our end sum is all we need for this
sum [] = Zero --base case
sum (h:t) = foldr (add) Zero (h:t) -- iterate

-- | An infinite list of all of the *odd* natural numbers, in order.
--
--   >>> map toInt (take 5 odds)
--   [1,3,5,7,9]
--
--   >>> toInt (sum (take 100 odds))
--   10000
--

--we will want to get a list of odds
odds :: [Nat] --odds will filter from isOdd
odds = filter isOdd nums

isOdd :: Nat -> Bool --takes nat, returns bool
isOdd Zero = False -- zero case, as zero is not odd
isOdd x = not ((mod (toInt x) 2) == 0) -- check if number is odd by using mod 2









--nums
nums :: [Nat] -- return number
nums = Zero : map (Succ) nums --returns number to be modified