/*
 * King.h
 *
 *  Created on: Jun 30, 2014
 *      Author: mlj
 */

#ifndef KING_H_
#define KING_H_

#include <vector>
#include "common.h"

class Board;

class King {
public:
    King();
    virtual ~King();
    static std::vector<movement> getMoves(movement & current, Board& board);
private:
    static bool isShortCastleAvailable(movement & current, Board& board);
    static bool isLongCastleAvailable(movement & current, Board& board);
};

#endif /* KING_H_ */
