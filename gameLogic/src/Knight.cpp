/*
 * Knight.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: mlj
 */

#include "Knight.h"
#include "Board.h"

using namespace std;

Knight::Knight() {
  // TODO Auto-generated constructor stub

}

Knight::~Knight() {
  // TODO Auto-generated destructor stub
}



vector<movement> Knight::getMoves(movement & current, Board& board){
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
