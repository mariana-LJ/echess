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

vector<square> Rook::getMoves(square & current, vector<vector<char> >& board){
	vector<square> possibleMoves;
	char color = (board[current.row][current.column] == 'R')? 'w': 'b';
	char pieceName = board[current.row][current.column];
	int temp_row = current.row;;
	int temp_col = current.column;

	//Top squares
	while(temp_row > 0){
		square newSquare;
		temp_row -= 1;
		newSquare.row = temp_row;
		newSquare.column = temp_col;
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
	temp_row = current.row;;
	temp_col = current.column;

	while(temp_col > 0){
		square newSquare;
		temp_col -= 1;
		newSquare.row = temp_row;
		newSquare.column = temp_col;
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
	temp_row = current.row;;
	temp_col = current.column;

	while(temp_row < 7){
		square newSquare;
		temp_row += 1;
		newSquare.row = temp_row;
		newSquare.column = temp_col;
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
	temp_row = current.row;;
	temp_col = current.column;

	while(temp_col < 7){
		square newSquare;
		temp_col += 1;
		newSquare.row = temp_row;
		newSquare.column = temp_col;
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
