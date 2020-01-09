-------------------------------------------------
-- Nicholas Skinner

-- CS 381 

-- 2/1/18

-- Assignment 2

-------------------------------------------------

module MiniLogo where

import Data.List 
import Prelude hiding (Num)

--
-- *****MiniLogo*****
--
--
--
--Starting with grammar
--
-- line:
-- grammar used:
--   num::= (meaning any natural number)
--   var::= (can be any variable name)
-- macro::= (can be any macro name)
--
-- prog::= ε|cmd; prog                 prog is the sequence of commands that will be used
--
-- mode ::= up|down                     pen's status adjuster
--
-- expr ::= var                           variable reference
--       | num                           Literal num/int
--       | expr + expr                   additional expressions
--
-- cmd::= pen mode                      canges pen status
--       | move (expr, expr)             moves pen to new position
--       | define macro (var*) {prog}    create/define a macro
--       | call macro (expr*)            call a macro



-- 1. Define the abstract syntax of MiniLogo as a set of Haskell data types. You should use built-in types for num, var, and macro. (If you want to define a type Num, you will have to hide that name from the Prelude).
--

type Num = Int
type Var = String
type Macro = String

type Prog = [Cmd]

-- the mode of the pen will either be up or down
data Mode = Up
          | Down
          deriving(Show,Eq)

-- expr's will be vars, nums (and exprs)
data Expr = Var Var
          | Num Num
          | Add Expr Expr
          deriving (Eq,Show)


		   -- cmd will control whole program, gives move, define, and call
		   -- is given instructions, and executes them
data Cmd = Pen Mode
         | Move Expr Expr
         | Define Macro [Var] Prog
         | Call Macro [Expr]
         deriving(Eq,Show)

-- 2. Define a MiniLogo macro line (x1,y1,x2,y2) that (starting from anywhere on the canvas) draws a line segment from (x1,y1) to (x2,y2).
-- Write the macro in MiniLogo concrete syntax (i.e. the notation defined by the grammar and used in the example programs above). Include this definition in a comment in your submission.
-- Encode the macro definition as a Haskell value using the data types defined in Task 1. This corresponds to the abstract syntax of MiniLogo. Your Haskell definition should start with something like line = Define "line" ...
--
-- Concrete Syntax from the provided example:
-- define line (x1, y1, x2, y2){
--     Pen Up;
--     Move (x1, y1);
--     Pen Down;
--     Move (x2, y2);
--     Pen Up;
-- }
line :: Cmd
line = Define "line" ["x1","y1","x2","y2"]
       [Pen Up,     Move (Var "x1") (Var "y1"),
        Pen Down,   Move (Var "x2") (Var "y2")]

-- 3. Use the line macro you just defined to define a new MiniLogo macro nix (x,y,w,h) that draws a big “X” of width w and height h, starting from position (x,y). Your definition should not contain any move commands.
-- Write the macro in MiniLogo concrete syntax and include this definition in a comment in your submission.
--Encode the macro definition as a Haskell value, representing the abstract syntax of the definition.
--
-- concrete syntax comment:
--
-- define nix (x, y, w, h) {
--   line(x, y, x + w, y + h);
--   line(x + w, y, x, y + h);
-- }
nix :: Cmd
nix = Define "nix" ["x","y","w","h"]
      [Call "line" [Var "x",Var "y",Add (Var "x") (Var "w"), Add (Var "y") (Var "h")],
       Call "line" [Add (Var "x") (Var "w"),Var "y",Var "x", Add (Var "y") (Var "h")]]

-- 4. Define a Haskell function steps :: Int -> Prog that constructs a MiniLogo program that draws a staircase of n steps starting from (0,0). Below is a visual illustration of what the generated program should draw for a couple different applications of steps.

--
-- we will not need to use define because this is a prog 
steps :: Int -> Prog
steps 0 = []
steps 1 = [Pen Up, Move (Num 0) (Num 0), Pen Down,
           Move (Num 0) (Num 1),Move (Num 1) (Num 1),
           Pen Up]
steps x = steps (pred x) ++ [Pen Up, Move (Num x) (Num x), Pen Down,
           Move (Num x) (Num (succ x)),Move (Num (succ x)) (Num (succ x)),
           Pen Up]

-- 5. Define a Haskell function macros :: Prog -> [Macro] that returns a list of the names of all of the macros that are defined anywhere in a given MiniLogo program. Don’t worry about duplicates—if a macro is defined more than once, the resulting list may include multiple copies of its name.
--
-- macros ((Define mac _ _): cmds)
-- macros ((Pen _): cmds)
-- macros ((Call _ _): cmds)  
-- macros ((Move _ _): cmds)   
macros :: Prog -> [Macro]
macros [] = []
macros ((Define mac _ _): cmds) = mac : macros cmds
macros ((Pen _): cmds)          = macros cmds
macros ((Call _ _): cmds)       = macros cmds
macros ((Move _ _): cmds)       = macros cmds


-- 6. Define a Haskell function pretty :: Prog -> String that pretty-prints a MiniLogo program. That is, it transforms the abstract syntax (a Haskell value) into nicely formatted concrete syntax (a string of characters). Your pretty-printed program should look similar to the example programs given above; however, for simplicity you will probably want to print just one command per line.
--In GHCi, you can render a string with newlines by applying the function putStrLn. So, to pretty-print a program p use: putStrLn (pretty p).
--
pretty :: Prog -> String
pretty [] = ""
pretty ((Pen p):cmds) = "(Pen " ++ (case p of
      Up -> "Up) "
      Down -> "Down) ") ++ pretty cmds ++ " "
pretty ((Move x y):cmds) = "Move (" ++  (prettyExpr x) ++ ") (" ++ (prettyExpr y) ++ ") " ++ pretty cmds ++ " "
pretty ((Call x y):cmds) = "Call " ++ x ++ " (" ++ concat (map prettyExpr y) ++ ") " ++ pretty cmds ++ " "
pretty ((Define x y z):cmds) = "Define " ++ x ++ "( (" ++ concat(intersperse " " y) ++ ") (" ++ pretty z ++"))" ++ pretty cmds ++ " "

--need to get int to string
--helper function show
--found at
--https://www.haskell.org/hoogle/?hoogle=Int+-%3E+String
prettyExpr :: Expr -> String
prettyExpr (Var x) = x 
prettyExpr (Num x) = (show x)
prettyExpr (Add x y) = "(Add " ++ "(" ++ prettyExpr x ++ ")" ++ "(" ++ prettyExpr y ++ ")) " 


--
-- *****BONUS STUFF*****
--
-- 7. Define a Haskell function optE :: Expr -> Expr that partially evaluates expressions by replacing any additions of literals with the result. For example, given the expression (2+3)+x, optE should return the expression 5+x.

--
optE :: Expr -> Expr
optE (Var x) = Var x 
optE (Num x) = Num x
optE (Add x y) = Add (optE x) (optE y)


-- | 8. Define a Haskell function optP :: Prog -> Prog that optimizes all of the expressions contained in a given program using optE.
--
optP :: Prog -> Prog
optP [] = []
optP (x:xs) = optPCmd x : optP xs 

--need a command method 

optPCmd :: Cmd -> Cmd
optPCmd (Call x y) = Call x (map optE y)
optPCmd (Move x y) = Move (optE x) (optE y)
optPCmd (Pen x) = (Pen x)