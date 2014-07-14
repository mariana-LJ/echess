/*
 * Knight.h
 *
 *  Created on: Jun 19, 2014
 *      Author: mlj
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_

#include <vector>
#include "common.h"

class Board;

class Knight {
public:
  Knight();
  virtual ~Knight();
  static std::vector<movement> getMoves(movement & current, Board& board);
};

#endif /* KNIGHT_H_ */
