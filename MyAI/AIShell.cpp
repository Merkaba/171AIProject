/*
For connect K, I've implemented an Iterative DFS and for my heuristic, I've made a small function which: 
Adds my piece to every empty piece in the board.
Count how many win conditions I have satisfied.
Adds opponents piece to every empty piece in the board. 
Count how many win conditions he has satisfied. 

My heuristic will be how valuable this world is to me 
(my win condition number vs his win condition number) and I'll do IDFS placing pieces in positions and seeing what this
similated world gets me for my heuristic.
Not sure if it's necessary to do branch pruning, so I've avoided it. Pruning can be done with a simple o(1) check if the 
current player can place a piece anywhere in the board and win on the next turn, so this is the only pruning done.
*/

#include "AIShell.h"
#include <iostream>
using namespace std;

/*
implements Depth First Search using gamestate. Accepts a gamestate and iteratively adds every possible move to that 
gamestate, which is then passed recursively to the function DFS with +1 depth. Once it reaches the last depth (set 
as 5 here), it will assign point values to the gamestates it has and cascades upwards until it returns to moveDFS. 
moveDFS then picks out the best possible gamestate and returns that as a move.
*/
Move moveDFS(int ** gameState, int numCols, int numRows, int depth, int maxDepth, int currPlayer, int k)
{
	Move move(NULL, NULL);
	int h_type;
	if (depth % 2 == 0)//get the max if even and min if odd
		h_type = 1;//1 = max, -1 = min
	else
		h_type = 0;
	int ** DFS_gameState = copyState(gameState, numCols, numRows);//copy of the state so i can edit it through the tree
																 
	int bestScore;
	int player;
	if (depth % 2 == 0)
	{
		player = -1;
		bestScore = -999;
	}
	else
	{
		player = 1;
		bestScore = 999;
	}

	for (int i = 0; i < numCols; i++)
	{
		if (lowestRow(DFS_gameState, i, numRows) == numRows)
			continue;
		else
		{
			DFS_gameState[i][lowestRow(DFS_gameState, i, numRows)] = currPlayer;
			int currentScore = DFS(DFS_gameState, numCols, numRows, depth + 1, maxDepth, player, k);
			if ((currentScore > bestScore) && (depth % 2 == 0))
			{
				bestScore = currentScore;
				move.row = i, move.col = lowestRow(DFS_gameState, i, numRows);
			}
			else if ((currentScore < bestScore) && (depth % 2 != 0))
			{
				bestScore = currentScore;
				move.row = i, move.col = lowestRow(DFS_gameState, i, numRows);
			}
		}
	}
	return move;
}

int DFS(int ** gameState, int numCols, int numRows, int depth, int maxDepth, int currPlayer, int k)
{
	Move move(NULL, NULL);
	int h_type;
	if (depth == maxDepth)
		return heuristic(gameState, numCols, numRows, k, currPlayer);
	else
	{
		if (depth % 2 == 0)//get the max if even and min if odd
			h_type = 1;//1 = max, -1 = min
		else
			h_type = 0;
		int ** DFS_gameState = copyState(gameState, numCols, numRows);//copy of the state so i can edit it through the tree. don't need this i think
																	  //need to do something for the move
		int bestScore;
		int player;
		if (depth % 2 == 0)
		{
			player = -1;
			bestScore = -999;
		}
		else
		{
			player = 1;
			bestScore = 999;
		}

		for (int i = 0; i < numCols; i++)
		{
			if (lowestRow(DFS_gameState, i, numRows) == numRows)
				continue;
			else
			{
				DFS_gameState[i][lowestRow(DFS_gameState, i, numRows)] = currPlayer;
				int currentScore = DFS(DFS_gameState, numCols, numRows, depth + 1, maxDepth, currPlayer, k);
				if ((currentScore > bestScore) && (depth % 2 == 0))
				{
					bestScore = currentScore;
					move.row = i, move.col = lowestRow(DFS_gameState, i, numRows);
				}
				else if ((currentScore < bestScore) && (depth % 2 != 0))
				{
					bestScore = currentScore;
					move.row = i, move.col = lowestRow(DFS_gameState, i, numRows);
				}
			}
		}
		//make a move here
		return bestScore;
	}
}

/*
Heurustic determines how favorable a gamestate is by scoring how many rows, columns, or diagnals are 
1 possible piece position away from winning, and then subtracting this from the opponents same score.
It doesn't matter if these piece positions are possible to get yet.

gameState denotes the 2dimensional current board.
numCols and numRows denotes number of columns and rows, respectively.
k denotes number of pieces needed to win.
currPlayer is 1 for you, -1 for opponent.
*/
int heuristic(int** gameState, int numCols, int numRows, int k, int currPlayer) {
	int playerScore = heuristicHelper(gameState, numCols, numRows, k, -1);
	int adversaryScore = heuristicHelper(gameState, numCols, numRows, k, 1);

	cout << "player score is " << playerScore << endl;
	cout << "adversary score is " << adversaryScore << endl;
	if (currPlayer == -1) {
		return playerScore - adversaryScore;
	}
	return adversaryScore - playerScore;
}

int heuristicHelper(int** gameState, int numCols, int numRows, int k, int currPlayer) {
	//check currPlayer's winning rows
	int counter = 0;
	int** h_gameState = copyState(gameState, numCols, numRows);
	for (int colPos = 0; colPos < numCols; colPos++) {
		for (int rowPos = 0; rowPos < numRows; rowPos++) {
			if (gameState[colPos][rowPos] != 0) {
				continue; //cant place a piece here! its taken!
			}
			
			h_gameState[colPos][rowPos] = currPlayer;
			if (checkWin(h_gameState, currPlayer, colPos, rowPos, k, numRows, numCols)) {
				counter++;
			}
			h_gameState[colPos][rowPos] = 0;
		
		}
	}
	return counter;
}

void freeState(int** gameState, int numCols) {
	for (int i = 0; i < numCols; i++) {
		delete[] gameState[i];
	}
	delete[] gameState;
}

int** copyState(int** gameState, int numCols, int numRows) {
	int** result = new int*[numCols];
	for (int i = 0; i < numCols; i++) {
		result[i] = new int[numRows];
	}
	for (int colPos = 0; colPos < numCols; colPos++) {
		for (int rowPos = 0; rowPos < numRows; rowPos++) {
			result[colPos][rowPos] = gameState[colPos][rowPos];
		}
	}
	return result;
}

/*
Checks for winning by locating streams of pieces using a vertical delta (-1, 0, or 1) and a
horizontal delta (-1, 0, or 1).
*/
bool checkWin(int** gameState, int currPlayer, int colPos,
	int rowPos, int k, int numRows, int numCols){
	if(checkWinHelper(gameState, currPlayer, colPos, rowPos, k, numRows, numCols,
		-1, -1)) {//225 deg
		return true;
	}
	if (checkWinHelper(gameState, currPlayer, colPos, rowPos, k, numRows, numCols,
		-1, 0)) {//270 deg
		return true;
	}
	if (checkWinHelper(gameState, currPlayer, colPos, rowPos, k, numRows, numCols,
		-1, 1)) {//315 deg
		return true;
	}
	if (checkWinHelper(gameState, currPlayer, colPos, rowPos, k, numRows, numCols,
		0, 1)) {//360 deg/0 deg
		return true;
	}
	if (checkWinHelper(gameState, currPlayer, colPos, rowPos, k, numRows, numCols,
		1, 1)) { //45deg
		return true;
	}
	if (checkWinHelper(gameState, currPlayer, colPos, rowPos, k, numRows, numCols,
		1, 0)) { //90 deg
		return true;
	}
	if (checkWinHelper(gameState, currPlayer, colPos, rowPos, k, numRows, numCols,
		1, -1)) { //135 deg 
		return true;
	}
	if (checkWinHelper(gameState, currPlayer, colPos, rowPos, k, numRows, numCols,
		0, -1)) {//180 deg
		return true;
	}
	return false;
}

bool checkWinHelper(int** gameState, int currPlayer, int colPos, 
	int rowPos, int k, int numRows, int numCols, int colD, int rowD ) {
	for (int i = 1; i < k; i++) { //check 1->k because 1 is 1 piece away from origin, which is already "good"
		int newCol = colPos + colD * i;
		int newRow = rowPos + rowD * i;
		if (!((newCol) < numCols && (newCol) >= 0)
			|| !((newRow) < numRows && (newRow) >= 0)
			|| gameState[newCol][newRow] != currPlayer)
			return false; 
			//return false if new colpos or rowpos is invalid or new space not occupied by currPlayer (and therefore not a win pos)
	}
	return true;
}

int lowestRow(int** gameState, int colPos, int numRows) {
	int result;
	for (result = numRows; result < numRows; result++) {
		if (gameState[colPos][result] == 0) {
			break;
		}
	}
	return result; //returns lowesty empty position in column, or numRows otherwise
}


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
}


AIShell::~AIShell()
{
	
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;

}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2
	
	return moveDFS(gameState, numCols, numRows, 0, 5, -1, this->k);
	 
}



