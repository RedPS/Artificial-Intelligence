/**
 * @file tictac_turnin.cc
 * 
 * @author Pedram Safaei
 * 
 * @version 1.2
 * 
 * @date 9/27/2018
 * 
 * @bug None that would break the grading system!
 * */

#include <tictac_support.h>
#include <stdio.h>
#include <iostream>

struct move{
	int Row=0;
	int Col=0;
};

int depth = 0; // so it can pick the win instead of going for a save I had to add tree depths to it

/**
 * @brief The minimax algorithm, which is the main goal of this assignment, it will try to find the best move
 * @param board, which is the board we are working with
 * @param computer, which is the player who's turn it is
 * @param notcomputer, is kinda our human, the person we are going against 
 * @return it will return the row and the column of the best move 
 * */
move MiniMaxAlg(int board[][3], int Computer, int NotComputer);
/**
 * @brief that's to make the minimax alg cleaner, made a separate function for searching for max
 * @param board, which is the board we are working with
 * @param computer, which is the player who's turn it is
 * @param notcomputer, is kinda our human, the person we are going against 
 * @param depth, so it can pick the win instead of going for a save I had to add tree depths to it
 * @return will return the best score
 * */
int SearchForMax(int board[][3],int Computer, int NotComputer, int depth);
/**
 * @brief that's to make the minimax alg cleaner, made a separate function for searching for min
 * @param board, which is the board we are working with
 * @param computer, which is the player who's turn it is
 * @param notcomputer, is kinda our human, the person we are going against 
 * @param depth, so it can pick the win instead of going for a save I had to add tree depths to it
 * @return will return the best score 
 * */
int SearchForMin(int board[][3], int Computer, int NotComputer, int depth);
/**
 * @brief check to see if we have a winning pattern
 * @param board, which is the board we are working with
 * @param state, check to see if the human is winning or the computer 
 * @return return true or false depending on if there is a winning pattern 
 * */
bool HasWon(int board[][3], int state);
/**
 * @brief check to see if we have tied at the end
 * @param board, which is the board we are working with
 * @return true or false, if there's a tie and there's no winning pattern then it is a tie
 * */
bool HasTied(int board[][3]);
/**
 * @brief we don't need this but it feels right to have something like this, check to see if the board is full if it is do not do anything
 * @param board, which is the board we are working with
 * @return true or false depending on if the board is full or not
 * */
bool BoardIsFull(int board[][3]);


int make_move( int board[][3] )
{
	// figure out what move it is
	int state = 0;
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			state += board[i][j];

	state = -state;
	if( state == 0 )
		state = 1;


	int Computer = state;
	int NotComputer = -state;

	if (BoardIsFull(board)){
		std::cout << "Board is Full so NO!" << std::endl;
	}
	else {
	move ChosenMove;
	ChosenMove = MiniMaxAlg(board, Computer, NotComputer);
	printf( "player [%d] made move: [%d,%d]\n", Computer, ChosenMove.Col, ChosenMove.Row );
	board[ChosenMove.Col][ChosenMove.Row] = Computer;
	}
	return 0;
}
move MiniMaxAlg(int board[][3], int Computer, int NotComputer){
	int score = 100000;
	move MOVE;
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == 0){
				board[i][j] = Computer; 
				int temp = SearchForMax(board, Computer, NotComputer, depth);
				if(temp < score){
					score = temp;
					MOVE.Col = i;
					MOVE.Row = j;
				}
				board[i][j] = 0;
			}
		}
	}
	return MOVE;
}

int SearchForMax(int board[][3], int Computer, int NotComputer, int depth){
	if (HasWon(board, NotComputer)){
		return 10;
	}
	else if (HasWon(board, Computer)){
		return -10;
	}
	else if (HasTied(board)){
		return 0;
	}
	int score = -100000;
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == 0){
				board[i][j] = NotComputer;
				score = std::max(score, SearchForMin(board, Computer, NotComputer, depth+1)-depth);
				board[i][j] = 0;
			}
		}
	}
	return score;
}
int SearchForMin(int board[][3],int Computer, int NotComputer, int depth){
	if (HasWon(board,NotComputer)){
		return 10;
	}
	else if (HasTied(board)){
		return 0;
	}
	else if (HasWon(board,Computer)){
		return -10;
	}
	int score = 100000;
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == 0){
				board[i][j] = Computer;
				score = std::min(score, SearchForMax(board, Computer, NotComputer, depth+1)+depth);
				board[i][j] = 0;
			}
		}
	}
	return score;
}

bool HasWon(int board[][3], int state){
	for (int i=0; i<3; i++){
		if(board[i][0] == state && 
		   board[i][1] == state && 
		   board[i][2] == state){
			return true;
		}
		if(board[0][i] == state &&
		   board[1][i] == state &&
		   board[2][i] == state){
			return true;
		}
	}
	if(board[0][0] == state &&
	   board[1][1] == state && 
	   board[2][2] == state){
		return true;
	}
	if(board[0][2] == state &&
	   board[1][1] == state &&
	   board[2][0] == state){
		return true;
	}
	return false;
}
bool HasTied(int board[][3]){
	for (int i=0; i<3; i++){
		if(board[i][0] == 0 ||
		   board[i][1] == 0 ||
		   board[i][2] == 0){
			   return false;
		   }
	}
	return true;
}

bool BoardIsFull(int board[][3]){
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == 0){
				return false;
			}
		}
	}
	return true;
}