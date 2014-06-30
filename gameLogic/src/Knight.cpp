/*
 * Knight.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: acp
 */

#include "Knight.h"

using namespace std;

Knight::Knight() {
  // TODO Auto-generated constructor stub

}

Knight::~Knight() {
  // TODO Auto-generated destructor stub
}


void Knight::ValidateMove(movement & move, char color, vector<vector<char> >& board, vector<movement> & possibleMoves) {
    if(move.target_row >= 0 && move.target_row <= 7 &&
       move.target_column >= 0 && move.target_column <= 7) {
        if(board[move.target_row][move.target_column] == '.' ){
            possibleMoves.push_back(move);
        }
        else if((color == 'w' && is_black(board[move.target_row][move.target_column])) ||
                (color == 'b' && is_white(board[move.target_row][move.target_column]))){
            possibleMoves.push_back(move);
        }
    }
}

vector<movement> Knight::getMoves(movement & current, vector<vector<char> >& board){
    vector<movement> possibleMoves;
    char color = (board[current.origin_row][current.origin_column] == 'N')? 'w': 'b';
    char pieceName = board[current.origin_row][current.origin_column];

    movement destination(current);

    destination.piece = pieceName;

    destination.target_row = current.origin_row + 1; // 1 place up
    destination.target_column = current.origin_column + 2; // 2 places right
    ValidateMove(destination, color, board, possibleMoves);

    destination.target_row = current.origin_row - 1; // 1 place down
    destination.target_column = current.origin_column + 2; // 2 places right
    ValidateMove(destination, color, board, possibleMoves);

    destination.target_row = current.origin_row + 2; // 2 places up
    destination.target_column = current.origin_column + 1; // 1 place right
    ValidateMove(destination, color, board, possibleMoves);

    destination.target_row = current.origin_row + 2; // 2 places up
    destination.target_column = current.origin_column - 1; // 1 place left
    ValidateMove(destination, color, board, possibleMoves);

    destination.target_row = current.origin_row + 1; // 1 place up
    destination.target_column = current.origin_column - 2; // 2 places to the left
    ValidateMove(destination, color, board, possibleMoves);

    destination.target_row = current.origin_row - 1; // 1 place down
    destination.target_column = current.origin_column - 2; // 2 places to the left
    ValidateMove(destination, color, board, possibleMoves);

    destination.target_row = current.origin_row - 2; // 2 places down
    destination.target_column = current.origin_column + 1; // 1 place right
    ValidateMove(destination, color, board, possibleMoves);

    destination.target_row = current.origin_row - 2; // 2 places down
    destination.target_column = current.origin_column - 1; // 1 place left
    ValidateMove(destination, color, board, possibleMoves);

    return possibleMoves;
}
