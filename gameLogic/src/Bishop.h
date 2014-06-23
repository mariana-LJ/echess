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

class Bishop {
public:
	Bishop();
	virtual ~Bishop();
	static std::vector<square> getMoves(square & current, std::vector<std::vector<char> >& board);
};

#endif /* BISHOP_H_ */
