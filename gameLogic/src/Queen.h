/*
 * Queen.h
 *
 *  Created on: Jun 30, 2014
 *      Author: mlj
 */

#ifndef QUEEN_H_
#define QUEEN_H_

#include <vector>
#include "common.h"
#include "Bishop.h"
#include "Rook.h"

class Board;

class Queen {
public:
    Queen();
    virtual ~Queen();
    static std::vector<movement> getMoves(movement & current, Board& board);
};


#endif /* QUEEN_H_ */
