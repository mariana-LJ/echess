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

class Pawn {
public:
  Pawn();
  virtual ~Pawn();
  static std::vector<movement> getMoves(movement & current, std::vector<std::vector<char> >& board);
private:
  static void takePiece(movement & move, char color, std::vector<std::vector<char> >& board, std::vector<movement> & possibleMoves);
  static void move(movement & move, char color, std::vector<std::vector<char> >& board, std::vector<movement> & possibleMoves);
};

#endif /* PAWN_H_ */
