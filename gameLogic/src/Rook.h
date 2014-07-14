/*
 * Rook.h
 *
 *  Created on: Jun 23, 2014
 *      Author: mlj
 */

#ifndef ROOK_H_
#define ROOK_H_

#include <vector>
#include "common.h"

class Board;

class Rook {
public:
	Rook();
	virtual ~Rook();
	static std::vector<movement> getMoves(movement & current, Board& board);
};

#endif /* ROOK_H_ */
