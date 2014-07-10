/*
 * King.cpp
 *
 *  Created on: Jun 30, 2014
 *      Author: mlj
 */

#include <iostream>
#include "King.h"
#include "common.h"

using namespace std;

King::King() {
    // TODO Auto-generated constructor stub

}

King::~King() {
    // TODO Auto-generated destructor stub
}

bool King::isShortCastleAvailable(movement & current, vector<vector<char> >& board){
    if(board[current.origin_row][current.origin_column] == 'K' &&
       (current.origin_row == 0 && current.origin_column == 4)){
        return(board[current.origin_row][current.origin_column + 1] == '.' &&
               board[current.origin_row][current.origin_column + 2] == '.' &&
               board[current.origin_row][current.origin_column + 3] == 'R');
    }
    else if(board[current.origin_row][current.origin_column] == 'k' &&
            (current.origin_row == 7 && current.origin_column == 4)){
        return(board[current.origin_row][current.origin_column + 1] == '.' &&
               board[current.origin_row][current.origin_column + 2] == '.' &&
               board[current.origin_row][current.origin_column + 3] == 'r');
    }
    else{
        return false;
    }
}

bool King::isLongCastleAvailable(movement & current, vector<vector<char> >& board){
    if(board[current.origin_row][current.origin_column] == 'K' &&
       (current.origin_row == 0 && current.origin_column == 4)){
        return(board[current.origin_row][current.origin_column - 1] == '.' &&
               board[current.origin_row][current.origin_column - 2] == '.' &&
               board[current.origin_row][current.origin_column - 3] == '.' &&
               board[current.origin_row][current.origin_column - 4] == 'R');
    }
    else if(board[current.origin_row][current.origin_column] == 'k' &&
            (current.origin_row == 7 && current.origin_column == 4)){
        return(board[current.origin_row][current.origin_column - 1] == '.' &&
               board[current.origin_row][current.origin_column - 2] == '.' &&
               board[current.origin_row][current.origin_column - 3] == '.' &&
               board[current.origin_row][current.origin_column - 4] == 'r');
    }
    else{
        return false;
    }
}

// No check, check mate or castle implemented yet
vector<movement> King::getMoves(movement & current, vector<vector<char> >& board){
    vector<movement> possibleMoves;

    char color = is_white(board[current.origin_row][current.origin_column])? 'w': 'b';
    char pieceName = board[current.origin_row][current.origin_column];

    movement newMove(current);
    newMove.piece = pieceName;


    // Possible moves in counter-clockwise
    // Upper right corner
    newMove.target_row = current.origin_row + 1;
    newMove.target_column = current.origin_column + 1;
    ValidateMove(newMove, color, board, possibleMoves);

    // Upper square
    newMove.target_row = current.origin_row + 1;
    newMove.target_column = current.origin_column;
    ValidateMove(newMove, color, board, possibleMoves);

    // Upper left corner
    newMove.target_row = current.origin_row + 1;
    newMove.target_column = current.origin_column - 1;
    ValidateMove(newMove, color, board, possibleMoves);

    // Left
    newMove.target_row = current.origin_row;
    newMove.target_column = current.origin_column - 1;
    ValidateMove(newMove, color, board, possibleMoves);

    // Lower left corner
    newMove.target_row = current.origin_row - 1;
    newMove.target_column = current.origin_column - 1;
    ValidateMove(newMove, color, board, possibleMoves);

    // Lower square
    newMove.target_row = current.origin_row - 1;
    newMove.target_column = current.origin_column;
    ValidateMove(newMove, color, board, possibleMoves);

    // Lower right corner
    newMove.target_row = current.origin_row - 1;
    newMove.target_column = current.origin_column + 1;
    ValidateMove(newMove, color, board, possibleMoves);

    // Right
    newMove.target_row = current.origin_row;
    newMove.target_column = current.origin_column + 1;
    ValidateMove(newMove, color, board, possibleMoves);

    // Short castle
    if(isShortCastleAvailable(current, board)){
        newMove.target_row = current.origin_row;
        newMove.target_column = current.origin_column + 2;
        possibleMoves.push_back(newMove);
    }

    // Long castle
    if(isLongCastleAvailable(current, board)){
        newMove.target_row = current.origin_row;
        newMove.target_column = current.origin_column - 2;
        possibleMoves.push_back(newMove);
    }

    return possibleMoves;
}

