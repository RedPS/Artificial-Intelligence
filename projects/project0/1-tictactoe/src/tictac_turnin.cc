#include <tictac_support.h>
#include <stdio.h>
#include <iostream>
#include <limits> // needed to set score to infinity (not really infinity but you know)

struct move{
	int y=0;
	int x=0;
};

int level = 0; // so it can pick the win instead of going for a save I had to add tree levels to it

move MiniMaxAlg(int board[][3], int Computer, int NotComputer);
int SearchForMax(int board[][3],int Computer, int NotComputer, int level);
int SearchForMin(int board[][3], int Computer, int NotComputer, int level);
bool HasWon(int board[][3], int state);
bool HasTied(int board[][3]);


/**
	make_move: takes a board state and makes a legal 
	(hopefully optimal) move

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		 -1: o
		
	returns (int):
		the number of steps it took to choose the best move
		(current implementation returns 1 by default, 0 if no move made)
**/

/*
 int MiniMaxAlg(depth, state){
     if (gameover || depth == 0)
        return score;
    
    //compute all legal moves for this state (player)

    Children = legalmoves(state);

    if (state == -1) //maximize
	bestscore = -infinity;

	for each child 
	{
		score = MiniMaxAlg(depth -1, 1);
		if(Score > bestscore)
			bestscore = score;
		return bestscore;
	}
	else if (state == 1) //minimize
	bestscore = +inf;
	for each child {
		score = MiniMaxAlg(depth -1; -1)
		if (score < bestscore)
			bestscore = score;
		return bestscore;
	}

 }
 */

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

	//std::cout << "Computer (AI)" << Computer << std::endl;
	//std::cout << "NotComputer " << NotComputer << std::endl;
   /*
	// default behavior: find any unoccupied square and make the move
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			// find an empty square
			if( board[i][j] == 0 )
			{
				// that's the move
				printf( "player [%d] made move: [%d,%d]\n", state, i, j );
				board[i][j] = state;
				return 1;
			}
	
	// no move was made (board was full)
	return 0;
	*/
	move ChosenMove;
	ChosenMove = MiniMaxAlg(board, Computer, NotComputer);
	printf( "player [%d] made move: [%d,%d]\n", Computer, ChosenMove.x, ChosenMove.y );
	board[ChosenMove.x][ChosenMove.y] = Computer;
	return 0;
}
move MiniMaxAlg(int board[][3], int Computer, int NotComputer){
	int score = std::numeric_limits<int>::max();
	move MOVE;
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == 0){
				board[i][j] = Computer; 
				int temp = SearchForMax(board, Computer, NotComputer, level);
				if(temp < score){
					score = temp;
					MOVE.x = i;
					MOVE.y = j;
				}
				board[i][j] = 0;
			}
		}
	}
	return MOVE;
}

int SearchForMax(int board[][3], int Computer, int NotComputer, int level){
	if (HasWon(board, NotComputer)){
		return 10;
	}
	else if (HasWon(board, Computer)){
		return -10;
	}
	else if (HasTied(board)){
		return 0;
	}
	int score = std::numeric_limits<int>::min();
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == 0){
				board[i][j] = NotComputer;
				score = std::max(score, SearchForMin(board, Computer, NotComputer, level+1)-level);
				board[i][j] = 0;
			}
		}
	}
	return score;
}
int SearchForMin(int board[][3],int Computer, int NotComputer, int level){
	if (HasWon(board,NotComputer)){
		return 10;
	}
	else if (HasTied(board)){
		return 0;
	}
	else if (HasWon(board,Computer)){
		return -10;
	}
	int score = std::numeric_limits<int>::max();
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == 0){
				board[i][j] = Computer;
				score = std::min(score, SearchForMax(board, Computer, NotComputer, level+1)+level);
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
