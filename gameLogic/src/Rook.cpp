/*
 * Rook.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: mlj
 */

#include "Rook.h"

using namespace std;

Rook::Rook() {
	// TODO Auto-generated constructor stub

}

Rook::~Rook() {
	// TODO Auto-generated destructor stub
}

vector<movement> Rook::getMoves(movement & current, vector<vector<char> >& board){
	vector<movement> possibleMoves;
	char color = (board[current.origin_row][current.origin_column] == 'R')? 'w': 'b';
	char pieceName = board[current.origin_row][current.origin_column];
	int temp_row = current.origin_row;;
	int temp_col = current.origin_column;

	//Top squares
	while(temp_row < 7){
		movement newMove;
		temp_row += 1;
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

	// Left squares
	temp_row = current.origin_row;;
	temp_col = current.origin_column;

	while(temp_col > 0){
		movement newMove;
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

	// Bottom squares
	temp_row = current.origin_row;;
	temp_col = current.origin_column;

	while(temp_row > 0){
		movement newMove;
		temp_row -= 1;
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

	// Right squares
	temp_row = current.origin_row;;
	temp_col = current.origin_column;

	while(temp_col < 7){
		movement newMove;
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
