# Nine Puzzle - An implementation of breadth-first search using hash tables

The Nine Puzzle is a square 3x3 tray in which are placed 8 square 1x1 tiles numbered from 1 to 8.  The remaining space is empty, so an adjacent tile can slide into that space, leaving its former location empty. Nine20 solves a nine puzzle given an INITIAL position (say 236158-47) and a GOAL position (say 12345678-).

To make the task more challenging, Nine20 uses breadth-first search to find some SHORTEST sequence (if one exists) with at most MAXSTEPS moves and prints out the complete sequence of positions separated by newlines.  For example,

```
% ./Nine20 100 236158-47 12345678-
  236158-47
  2361584-7
  23615847-
  23615-478
  23-156478
  2-3156478
  -23156478
  123-56478
  123456-78
  1234567-8
  12345678-
```
If no such move sequence exists, then nothing is printed; e.g.,

 ` % ./Nine20 8 236158-47 12345678-`

(since the shortest sequence has 10 moves) or

 ` % ./Nine20 100 12345678- 12345687-`

(since there is no sequence of moves from 12345678- to 12345687-.

The label on each tile can be any single printing character other than -, which denotes the empty square, but the labels may not be unique. 
