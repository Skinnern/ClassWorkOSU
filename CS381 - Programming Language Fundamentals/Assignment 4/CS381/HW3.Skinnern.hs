module HW3 where

import MiniMiniLogo
import Render


--
-- * Semantics of MiniMiniLogo
--

-- NOTE:
--   * MiniMiniLogo.hs defines the abstract syntax of MiniMiniLogo and some
--     functions for generating MiniMiniLogo programs. It contains the type
--     definitions for Mode, Cmd, and Prog.
--   * Render.hs contains code for rendering the output of a MiniMiniLogo
--     program in HTML5. It contains the types definitions for Point and Line.

-- | A type to represent the current state of the pen.
type State = (Mode,Point)

-- | The initial state of the pen.
start :: State
start = (Up,(0,0))

-- | A function that renders the image to HTML. Only works after you have
--   implemented `prog`. Applying `draw` to a MiniMiniLogo program will
--   produce an HTML file named MiniMiniLogo.html, which you can load in
--   your browswer to view the rendered image.
draw :: Prog -> IO ()
draw p = let (_,ls) = prog p start in toHTML ls


-- Semantic domains:
--   * Cmd:  State -> (State, Maybe Line)
--   * Prog: State -> (State, [Line])


-- | Semantic function for Cmd.
--   
--   >>> cmd (Pen Down) (Up,(2,3))
--   ((Down,(2,3)),Nothing)
--
--   >>> cmd (Pen Up) (Down,(2,3))
--   ((Up,(2,3)),Nothing)
--
--   >>> cmd (Move 4 5) (Up,(2,3))
--   ((Up,(4,5)),Nothing)
--
--   >>> cmd (Move 4 5) (Down,(2,3))
--   ((Down,(4,5)),Just ((2,3),(4,5)))
--
cmd :: Cmd -> State -> (State, Maybe Line)
cmd (Pen x)(_,pt)=((x,pt), Nothing)
cmd (Move m1 m2)(Down,pt)=((Down,(m1,m2)), Just((pt),(m1,m2)))
cmd (Move m1 m2)(Up,pt)=((Up,(m1,m2)), Nothing)


-- | Semantic function for Prog.
--
--   >>> prog (nix 10 10 5 7) start
--   ((Down,(15,10)),[((10,10),(15,17)),((10,17),(15,10))])
--
--   >>> prog (steps 2 0 0) start
--   ((Down,(2,2)),[((0,0),(0,1)),((0,1),(1,1)),((1,1),(1,2)),((1,2),(2,2))])
prog :: Prog -> State -> (State, [Line])
prog prgs st = (progHelp prgs (st,[]))

progHelp :: Prog ->(State, [Line]) -> (State, [Line])
progHelp [] x = x
progHelp (prg:prgs) (st,ls) = 
    let (nexst,nexln) = cmd prg st in
    case nexln of 
        Just nexln -> progHelp prgs (nexst, ls ++ [nexln])
        Nothing -> progHelp prgs (nexst,ls)



--easyRender (prog amazing start)
easyRender :: (State,[Line]) -> IO()
easyRender (_,xs) = toHTML xs
--
-- * Extra credit
--

-- | This should be a MiniMiniLogo program that draws an amazing picture.
--   Add as many helper functions as you want.
amazing :: Prog
amazing = [Pen Up, Move 4 2,Pen Down, Move 4 38, Move 76 38, Move 76 2, Move 4 2,Pen Up] ++ 
          [Pen Up, Move 8 4,Pen Down, Move 8 36, Move 72 36, Move 72 4, Move 8 4,Pen Up] ++
          [Pen Up, Move 12 6,Pen Down, Move 12 34, Move 68 34, Move 68 6, Move 12 6,Pen Up] ++
          [Pen Up, Move 16 8,Pen Down, Move 16 32, Move 64 32, Move 64 8, Move 16 8,Pen Up] ++
          [Pen Up, Move 18 9,Pen Down, Move 18 31, Move 62 31, Move 62 9, Move 18 9,Pen Up] ++
          [Pen Up, Move 20 10,Pen Down, Move 20 30, Move 60 30, Move 60 10, Move 20 10,Pen Up] ++
          [Pen Up, Move 22 11,Pen Down, Move 22 29, Move 58 29, Move 58 11, Move 22 11,Pen Up] ++
          [Pen Up, Move 24 12,Pen Down, Move 24 28, Move 56 28, Move 56 12, Move 24 12,Pen Up] ++
          [Pen Up, Move 26 13,Pen Down, Move 26 27, Move 54 27, Move 54 13, Move 26 13,Pen Up] ++
          [Pen Up, Move 28 14,Pen Down, Move 28 26, Move 52 26, Move 52 14, Move 28 14,Pen Up] ++
          [Pen Up, Move 0 0,Pen Down, Move 30 15, Pen Up] ++
          [Pen Up, Move 80 0,Pen Down, Move 50 15, Pen Up] ++
          [Pen Up, Move 0 40,Pen Down, Move 30 25, Pen Up] ++
          [Pen Up, Move 80 40,Pen Down, Move 50 25, Pen Up] ++
          [Pen Up, Move 50 25,Pen Down, Move 30 25, Move 30 15, Move 50 15, Move 50 25,Pen Up] 