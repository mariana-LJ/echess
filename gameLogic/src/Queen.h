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

class Queen {
public:
    Queen();
    virtual ~Queen();
    static std::vector<movement> getMoves(movement & current, std::vector<std::vector<char> >& board);
};


#endif /* QUEEN_H_ */
