/*
 * Pawn.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: acp
 */

#include "Pawn.h"

using namespace std;

Pawn::Pawn() {
  // TODO Auto-generated constructor stub

}

Pawn::~Pawn() {
  // TODO Auto-generated destructor stub
}

void Pawn::takePiece(movement & move, char color, vector<vector<char> >& board, vector<movement> & possibleMoves){
    if(move.target_row >= 0 && move.target_row <= 7 &&
       move.target_column >= 0 && move.target_column <= 7) {
        if((color == 'w' && is_black(board[move.target_row][move.target_column])) ||
           (color == 'b' && is_white(board[move.target_row][move.target_column]))){
            possibleMoves.push_back(move);
        }
    }
}

void Pawn::move(movement & move, char color, vector<vector<char> >& board, vector<movement> & possibleMoves){
    if(move.target_row >= 0 && move.target_row <= 7 &&
       move.target_column >= 0 && move.target_column <= 7) {
        if(board[move.target_row][move.target_column] == '.' ){
            possibleMoves.push_back(move);
        }
    }
}

vector<movement> Pawn::getMoves(movement & current, vector<vector<char> >& board){
    // No en passant or promotion considered yet
    vector<movement> possibleMoves;
    char color = (board[current.origin_row][current.origin_column] == 'P')? 'w': 'b';
    char pieceName = board[current.origin_row][current.origin_column];

    movement newMove(current);
    newMove.piece = pieceName;

    if(color == 'w'){
        newMove.target_row = current.origin_row + 1;
        newMove.target_column = current.origin_column;
        move(newMove, color, board, possibleMoves);
        if(current.origin_row == 1){ // the first move for a white pawn
          newMove.target_row = current.origin_row + 2; // check two squares ahead
          move(newMove, color, board, possibleMoves);
        }

        // check if white can take a black piece to the left
        newMove.target_row = current.origin_row + 1;
        newMove.target_column = current.origin_column - 1;
        takePiece(newMove, color, board, possibleMoves);

        // check if white can take a black piece to the right
        newMove.target_row = current.origin_row + 1;
        newMove.target_column = current.origin_column + 1;
        takePiece(newMove, color, board, possibleMoves);

    }
    else{
        newMove.target_row = current.origin_row - 1;
        newMove.target_column = current.origin_column;
        move(newMove, color, board, possibleMoves);
        if(current.origin_row == 6){ // the first move for a black pawn
          newMove.target_row = current.origin_row - 2; // check two squares ahead
          move(newMove, color, board, possibleMoves);
        }

        // check if black can take a white piece to the left
        newMove.target_row = current.origin_row - 1;
        newMove.target_column = current.origin_column - 1;
        takePiece(newMove, color, board, possibleMoves);

        // check if black can take a white piece to the right
        newMove.target_row = current.origin_row - 1;
        newMove.target_column = current.origin_column + 1;
        takePiece(newMove, color, board, possibleMoves);

  }
  return possibleMoves;
}

