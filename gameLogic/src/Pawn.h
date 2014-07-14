/*
 * Pawn.h
 *
 *  Created on: Jun 19, 2014
 *      Author: mlj
 */

#ifndef PAWN_H_
#define PAWN_H_

#include <vector>
#include "common.h"

class Board;

class Pawn {
public:
  Pawn();
  virtual ~Pawn();
  static std::vector<movement> getMoves(movement & current, Board& board);
private:
  static void takePiece(movement & move, char color, Board& board, std::vector<movement> & possibleMoves);
  static void move(movement & move, char color, Board& board, std::vector<movement> & possibleMoves);
};

#endif /* PAWN_H_ */
