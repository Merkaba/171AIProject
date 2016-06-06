# 171AIProject

A project for the Introduction to Aritifical intelligence class. I created an AI plugin for a Connect-4 (In truth, connect-X) game which could play against either human opponents or AI opponents when plugged into a game. The AI utilizes a depth-first search to look through possible game states in the current game. Using these possible gamestates, it evaluates each gamestate and maximizes the best possible move for us while minimizing the enemy's best move impact, assuming he runs the optimal path. 

The portion of work I was responsible for was implementing an AI that could decide optimal moves when provided a gamestate and send it  via API as called. My AI is located in the folder 'MyAI', the rest was provided by the class.

## AIShell.cpp and AIShell.h 
A function, **moveDFS**, implements Depth First Search using gamestate. It accepts a gamestate and iteratively adds every possible move to that gamestate, which is then passed recursively to the function **DFS** with +1 depth. Once it reaches the last depth (set as 5 here), it will assign point values to the gamestates it has and cascades upwards until it returns to moveDFS. moveDFS then picks out the best possible gamestate and returns that as a move.

A function, **heurustic** determines how favorable a gamestate is by scoring how many rows, columns, or diagnals are 1 possible piece position away from winning, and then subtracting this from the opponents same score.

A function, **checkWin**, determines if a state has won for the current player or not. 

## ConnectK.cpp 

A function, **makeAIShellFromInput**, sets up the gamestate which AI receives, including all current piece positions, how many pieces are required to win, number of rows and columns, how long we have to make a move, and if gravity is turned on or off (gravity off allows players to place a piece anywhere on the board, not just the lowest row in a column).

## Move.cpp and Move.h
The basic files which allow the program to request and receive a next move.
