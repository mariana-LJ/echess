/*
 * Bishop.h
 *
 *  Created on: Jun 20, 2014
 *      Author: mlj
 */

#ifndef BISHOP_H_
#define BISHOP_H_

#include <vector>
#include "common.h"

class Board;

class Bishop {
public:
	Bishop();
	virtual ~Bishop();
	static std::vector<movement> getMoves(movement & current, Board& board);
};

#endif /* BISHOP_H_ */
