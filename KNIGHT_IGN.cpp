/**
 * File: Knight_IGN.cpp
 * --------------------
 * Andrew Adams
 * Implements a Bread-first search to find how many move iterations until every square is within strikable reach of a knight.
 * I make use of the CS106b libraries implementation of 'Grid' (a simplified 2x2 array) and Queue (a modification of the STL version).
 * It was just easier for me, given that for a Stanford class I wrote another breadth-first algorithim in C++ using those libraries :-).
 */

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include "genlib.h"
#include "strutils.h"
#include "simpio.h"
#include "grid.h"
#include "queue.h"


/*
 * Constants for board dimension; starting location of knight; and unvisited square
 */
const int BOARD_DIM = 8;
const int STARTX=6;
const int STARTY=0;
const int NOT_VISITED=0;
const char UNMARKED = '*';

/*
 * Structure for a given path that holds the int for number of moves, and the current x&y location on the board.
 */
struct Path{
	int currX;
	int currY;
	int numMoves;
};


/* 
 * Function Prototypes
 */
void RunTour();
Grid<int> InitBoard();
void EnqueueMoves(Path path, Queue<Path> &queue, Grid<int> &board);
void AddIfInBounds (int x, int y, Path path, Queue<Path> &queue, Grid<int> &board);
void PrintBoard(Grid<int> &board, Path &path);

int main() {
	cout << "This program runs a breath first search to determine the number of moves it takes for a knight to cover the whole board."<<endl;
	cout << "Each square of the board is marked by the move on which it is potentially visitable, while unmarked squares are flagged with '"<< UNMARKED<<"'."<<endl;
	cout << endl;
	cout << "Press enter when ready to begin!"<<endl;
	GetLine();
	RunTour();
	return 0;
}

/* Initializes a board where every square is marked as unvisited, except for the starting location of the knight,
 * which is marked as an increment higher than NOT_VISITED
 */
Grid<int> InitBoard() {
	Grid<int> board (BOARD_DIM, BOARD_DIM);
	for (int i=0; i<BOARD_DIM; i++){
		for (int j=0; j<BOARD_DIM; j++){
			board[i][j]=NOT_VISITED;
		}
		board[STARTX][STARTY]=NOT_VISITED+1;
	}
	return board;
	
}

/* Increments move iteration, and forwards moving of viable moves to a helper function
 */
void EnqueueMoves(Path path, Queue<Path> &queue, Grid<int> &board){
	path.numMoves++; 
	AddIfInBounds(path.currX + 1, path.currY - 2, path, queue, board);
	AddIfInBounds(path.currX + 1, path.currY + 2, path, queue, board);
	AddIfInBounds(path.currX + 2, path.currY - 1, path, queue, board);
	AddIfInBounds(path.currX + 2, path.currY + 1, path, queue, board);
	AddIfInBounds(path.currX - 2, path.currY - 1, path, queue, board);
	AddIfInBounds(path.currX - 2, path.currY + 1, path, queue, board);
	AddIfInBounds(path.currX - 1, path.currY - 2, path, queue, board);
	AddIfInBounds(path.currX - 1, path.currY + 2, path, queue, board);
	
}

/* Checks if a move is within bounds, if it is, it adds it to the queue!
 */
void AddIfInBounds (int x, int y, Path path, Queue<Path> &queue, Grid<int> &board){
	path.currX=x;
	path.currY=y;
	if (path.currX>= 0 && path.currX < BOARD_DIM && path.currY >= 0 && path.currY<BOARD_DIM && board[x][y]==NOT_VISITED){
		queue.enqueue(path);
		board[x][y]=path.numMoves;
	}	
}

/* Runs a breadth-first, queue-based algorithim to find minimum number of moves until the entire board has been 'covered'. 
*/
void RunTour(){
	Path path; 
	Queue<Path >queue;
	Grid<int> board= InitBoard();
	int iterations=NOT_VISITED;
	path.numMoves=NOT_VISITED;
	path.currX=STARTX;
	path.currY=STARTY;
	queue.enqueue(path);
	while (!queue.isEmpty()) {  
		path = queue.dequeue(); 
		if (path.numMoves>iterations){
			iterations=path.numMoves;
			PrintBoard (board, path);
		}
		EnqueueMoves(path, queue, board);
	}
}
	

/* Given an anysize board of unmarked integers, this function prints out each square, and marks whether it has been
 * visited, and if so, on which move iteration.
 */
void PrintBoard(Grid<int> &board, Path &path){
	cout << endl << "Move Iteration number" << path.numMoves  << endl;
	cout << "Board at current iteration:" << endl;
	for (int i = 0; i < BOARD_DIM; i++) {
		for (int j = 0; j < BOARD_DIM; j++) {
			if (board[j][i] > NOT_VISITED) {
				cout << " " << board[j][i]-1 << " ";
			}
			else {
				cout << " "<<UNMARKED<<" ";
			}
		}
		cout << endl;
	}
}