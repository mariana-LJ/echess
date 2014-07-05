/*
 * Queen.cpp
 *
 *  Created on: Jun 30, 2014
 *      Author: mlj
 */

#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

using namespace std;

Queen::Queen() {
    // TODO Auto-generated constructor stub

}

Queen::~Queen() {
    // TODO Auto-generated destructor stub
}

vector<movement> Queen::getMoves(movement & current, vector<vector<char> >& board){
    vector<movement> possibleMoves;
    vector<movement> rowColMoves;
    char color = (board[current.origin_row][current.origin_column] == 'B')? 'w': 'b';
    char pieceName = board[current.origin_row][current.origin_column];

    possibleMoves = Bishop::getMoves(current, board);
    rowColMoves = Rook::getMoves(current, board);

    possibleMoves.insert(possibleMoves.end(), rowColMoves.begin(), rowColMoves.end());

    return possibleMoves;
}
