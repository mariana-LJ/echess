/*
 * Bishop.cpp
 *
 *  Created on: Jun 20, 2014
 *      Author: mlj
 */

#include "Bishop.h"

using namespace std;

Bishop::Bishop() {
	// TODO Auto-generated constructor stub

}

Bishop::~Bishop() {
	// TODO Auto-generated destructor stub
}

vector<movement> Bishop::getMoves(movement & current, vector<vector<char> >& board){
	vector<movement> possibleMoves;
	char color = (board[current.origin_row][current.origin_column] == 'B')? 'w': 'b';
	char pieceName = board[current.origin_row][current.origin_column];
	int temp_row = current.origin_row;;
	int temp_col = current.origin_column;

	//Upper right diagonal
	while((temp_row < 7) && (temp_col < 7)){
		movement newMove;
		temp_row += 1;
		temp_col += 1;
		newMove.target_row = temp_row;
		newMove.target_column = temp_col;
		newMove.piece = board[temp_row][temp_col];

		if(newMove.piece == '.' ){
			possibleMoves.push_back(newMove);
		}
		else if((color == 'w' && is_black(newMove.piece)) ||
				(color == 'b' && is_white(newMove.piece))){
		    possibleMoves.push_back(newMove);
		}
		else{
			break;
		}
	}

	//Upper left diagonal
	temp_row = current.origin_row;
	temp_col = current.origin_column;

	while((temp_row < 7) && (temp_col > 0)){
		movement newMove;
		temp_row += 1;
		temp_col -= 1;
		newMove.target_row = temp_row;
		newMove.target_column = temp_col;
		newMove.piece = board[temp_row][temp_col];

		if(newMove.piece == '.' ){
			possibleMoves.push_back(newMove);
		}
		else if((color == 'w' && is_black(newMove.piece)) ||
				(color == 'b' && is_white(newMove.piece))){
		    possibleMoves.push_back(newMove);
		}
		else{
			break;
		}
	}

	//Lower left diagonal
	temp_row = current.origin_row;
	temp_col = current.origin_column;

	while((temp_row > 0) && (temp_col > 0)){
		movement newMove;
		temp_row -= 1;
		temp_col -= 1;
		newMove.target_row = temp_row;
		newMove.target_column = temp_col;
		newMove.piece = board[temp_row][temp_col];

		if(newMove.piece == '.' ){
			possibleMoves.push_back(newMove);
		}
		else if((color == 'w' && is_black(newMove.piece)) ||
				(color == 'b' && is_white(newMove.piece))){
		    possibleMoves.push_back(newMove);
		}
		else{
			break;
		}
	}

	// Lower right diagonal
	temp_row = current.origin_row;
	temp_col = current.origin_column;

	while((temp_row > 0) && (temp_col < 7)){
		movement newMove;
		temp_row -= 1;
		temp_col += 1;
		newMove.target_row = temp_row;
		newMove.target_column = temp_col;
		newMove.piece = board[temp_row][temp_col];

		if(newMove.piece == '.' ){
			possibleMoves.push_back(newMove);
		}
		else if((color == 'w' && is_black(newMove.piece)) ||
				(color == 'b' && is_white(newMove.piece))){
		    possibleMoves.push_back(newMove);
		}
		else{
			break;
		}
	}

	return possibleMoves;
}
