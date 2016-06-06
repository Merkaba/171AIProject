# 171AIProject
A project for the Introduction to Aritifical intelligence class. I created an AI plugin for a Connect-4 (In truth, connect-X) game which could play against either human opponents or AI opponents when plugged into a game. The AI utilizes a depth-first search to look through possible game states in the current game. Using these possible gamestates, it evaluates each gamestate and maximizes the best possible move for us while minimizing the enemy's best move impact, assuming he runs the optimal path. 

The portion of work I was responsible for was implementing an AI that could decide optimal moves when provided a gamestate and send it  via API as called. My AI is located in the folder 'MyAI', the rest was provided by the class.

In the 'MyAI' folder, there are several files:
AIShell.cpp and AIShell.h implements the depth first search using gamestate, a heuristic function to determine how favorable a gamestate is, and a checkWin function to determine if a state has won or not. 

ConnectK.cpp sets up the gamestate that I receive, including all current piece positions, how many pieces are required to win, number of rows and columns, how long we have to make a move, and if gravity is turned on or off (gravity off allows players to place a piece anywhere on the board, not just the lowest row in a column).

Move.cpp and Move.h are the basic files which allow the program to request and receive a next move.
