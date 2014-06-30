/*
 * Knight.h
 *
 *  Created on: Jun 19, 2014
 *      Author: acp
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_

#include <vector>
#include "common.h"

class Knight {
public:
  Knight();
  virtual ~Knight();
  static std::vector<movement> getMoves(movement & current, std::vector<std::vector<char> >& board);
};

#endif /* KNIGHT_H_ */
