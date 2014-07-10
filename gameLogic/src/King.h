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

class King {
public:
    King();
    virtual ~King();
    static std::vector<movement> getMoves(movement & current, std::vector<std::vector<char> >& board);
private:
    static bool isShortCastleAvailable(movement & current, std::vector<std::vector<char> >& board);
    static bool isLongCastleAvailable(movement & current, std::vector<std::vector<char> >& board);
};

#endif /* KING_H_ */
