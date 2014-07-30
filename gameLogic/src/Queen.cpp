/*
 * Queen.cpp
 *
 *  Created on: Jun 30, 2014
 *      Author: mlj
 */

#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Board.h"

using namespace std;

vector<movement> Queen::getMoves(movement & current, Board& board){
    vector<movement> possibleMoves;
    vector<movement> rowColMoves;

    possibleMoves = Bishop::getMoves(current, board);
    rowColMoves = Rook::getMoves(current, board);

    possibleMoves.insert(possibleMoves.end(), rowColMoves.begin(), rowColMoves.end());

    return possibleMoves;
}
