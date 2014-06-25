/*
 * Pawn.h
 *
 *  Created on: Jun 19, 2014
 *      Author: acp
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
};

#endif /* PAWN_H_ */
