/*
 * Rook.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: mlj
 */

#include "Rook.h"
#include "Board.h"

using namespace std;

vector<movement> Rook::getMoves(movement & current, Board& board){
	vector<movement> possibleMoves;
	char color = is_white(board[current.origin_row][current.origin_column])? 'w': 'b';
	char pieceName = board[current.origin_row][current.origin_column];
	int temp_row = current.origin_row;;
	int temp_col = current.origin_column;

	movement newMove(current);
	newMove.piece = pieceName;

	//Top squares
	while(temp_row < 7){
		temp_row += 1;
		newMove.target_row = temp_row;
		newMove.target_column = temp_col;

        ValidateMove(newMove, color, board, possibleMoves);

        if(board[newMove.target_row][newMove.target_column] != '.' ){
            break;
        }
	}

	// Left squares
	temp_row = current.origin_row;;
	temp_col = current.origin_column;

	while(temp_col > 0){
		temp_col -= 1;
		newMove.target_row = temp_row;
		newMove.target_column = temp_col;

        ValidateMove(newMove, color, board, possibleMoves);

        if(board[newMove.target_row][newMove.target_column] != '.' ){
            break;
        }
	}

	// Bottom squares
	temp_row = current.origin_row;;
	temp_col = current.origin_column;

	while(temp_row > 0){
		temp_row -= 1;
		newMove.target_row = temp_row;
		newMove.target_column = temp_col;

        ValidateMove(newMove, color, board, possibleMoves);

        if(board[newMove.target_row][newMove.target_column] != '.' ){
            break;
        }
	}

	// Right squares
	temp_row = current.origin_row;;
	temp_col = current.origin_column;

	while(temp_col < 7){
		temp_col += 1;
		newMove.target_row = temp_row;
		newMove.target_column = temp_col;

        ValidateMove(newMove, color, board, possibleMoves);

        if(board[newMove.target_row][newMove.target_column] != '.' ){
            break;
        }
	}

	return possibleMoves;
}
