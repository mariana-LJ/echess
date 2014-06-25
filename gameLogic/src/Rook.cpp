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
	char color = (board[current.target_row][current.target_column] == 'R')? 'w': 'b';
	char pieceName = board[current.target_row][current.target_column];
	int temp_row = current.target_row;;
	int temp_col = current.target_column;

	//Top squares
	while(temp_row > 0){
		movement newSquare;
		temp_row -= 1;
		newSquare.target_row = temp_row;
		newSquare.target_column = temp_col;
		newSquare.piece = board[temp_row][temp_col];

		if(newSquare.piece == '.' ){
			possibleMoves.push_back(newSquare);
		}
		else if((color == 'w' && newSquare.piece > 'a') ||
			(color == 'b' && newSquare.piece < 'a')){
		    possibleMoves.push_back(newSquare);
		}
		else{
			break;
		}
	}

	// Left squares
	temp_row = current.target_row;;
	temp_col = current.target_column;

	while(temp_col > 0){
		movement newSquare;
		temp_col -= 1;
		newSquare.target_row = temp_row;
		newSquare.target_column = temp_col;
		newSquare.piece = board[temp_row][temp_col];

		if(newSquare.piece == '.' ){
			possibleMoves.push_back(newSquare);
		}
		else if((color == 'w' && newSquare.piece > 'a') ||
			(color == 'b' && newSquare.piece < 'a')){
		    possibleMoves.push_back(newSquare);
		}
		else{
			break;
		}
	}

	// Bottom squares
	temp_row = current.target_row;;
	temp_col = current.target_column;

	while(temp_row < 7){
		movement newSquare;
		temp_row += 1;
		newSquare.target_row = temp_row;
		newSquare.target_column = temp_col;
		newSquare.piece = board[temp_row][temp_col];

		if(newSquare.piece == '.' ){
			possibleMoves.push_back(newSquare);
		}
		else if((color == 'w' && newSquare.piece > 'a') ||
			(color == 'b' && newSquare.piece < 'a')){
		    possibleMoves.push_back(newSquare);
		}
		else{
			break;
		}
	}

	// Right squares
	temp_row = current.target_row;;
	temp_col = current.target_column;

	while(temp_col < 7){
		movement newSquare;
		temp_col += 1;
		newSquare.target_row = temp_row;
		newSquare.target_column = temp_col;
		newSquare.piece = board[temp_row][temp_col];

		if(newSquare.piece == '.' ){
			possibleMoves.push_back(newSquare);
		}
		else if((color == 'w' && newSquare.piece > 'a') ||
			(color == 'b' && newSquare.piece < 'a')){
		    possibleMoves.push_back(newSquare);
		}
		else{
			break;
		}
	}

	return possibleMoves;
}
