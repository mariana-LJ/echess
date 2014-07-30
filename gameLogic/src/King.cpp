/*
 * King.cpp
 *
 *  Created on: Jun 30, 2014
 *      Author: mlj
 */

#include <iostream>
#include "King.h"
#include "common.h"
#include "Board.h"

using namespace std;

bool King::isShortCastleAvailable(movement & current, Board& board){
    if(current.origin_row == 0){
        return(board.whiteShortCastleAvailable() &&
               board[current.origin_row][current.origin_column + 1] == '.' &&
               board[current.origin_row][current.origin_column + 2] == '.');
    }
    else if(current.origin_row == 7){
        return(board.blackShortCastleAvailable() &&
               board[current.origin_row][current.origin_column + 1] == '.' &&
               board[current.origin_row][current.origin_column + 2] == '.');
    }
    else{
        return false;
    }
}

bool King::isLongCastleAvailable(movement & current, Board& board){
    if(current.origin_row == 0){
        return(board.whiteLongCastleAvailable() &&
               board[current.origin_row][current.origin_column - 1] == '.' &&
               board[current.origin_row][current.origin_column - 2] == '.' &&
               board[current.origin_row][current.origin_column - 3] == '.');
    }
    else if(current.origin_row == 7){
        return(board.blackLongCastleAvailable() &&
               board[current.origin_row][current.origin_column - 1] == '.' &&
               board[current.origin_row][current.origin_column - 2] == '.' &&
               board[current.origin_row][current.origin_column - 3] == '.');
    }
    else{
        return false;
    }
}

// No check, check mate or castle implemented yet
vector<movement> King::getMoves(movement & current, Board& board){
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

