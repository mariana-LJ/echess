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
	char color = (board[current.target_row][current.target_column] == 'B')? 'w': 'b';
	char pieceName = board[current.target_row][current.target_column];
	int temp_row = current.target_row;;
	int temp_col = current.target_column;

	//Upper right diagonal
	while((temp_row > 0) && (temp_col < 7)){
		movement newSquare;
		temp_row -= 1;
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

	//Upper left diagonal
	temp_row = current.target_row;
	temp_col = current.target_column;

	while((temp_row > 0) && (temp_col > 0)){
		movement newSquare;
		temp_row -= 1;
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

	//Lower left diagonal
	temp_row = current.target_row;
	temp_col = current.target_column;

	while((temp_row < 7) && (temp_col > 0)){
		movement newSquare;
		temp_row += 1;
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

	// Lower right diagonal
	temp_row = current.target_row;
	temp_col = current.target_column;

	while((temp_row < 7) && (temp_col < 7)){
		movement newSquare;
		temp_row += 1;
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
