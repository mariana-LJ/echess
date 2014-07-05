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
};

#endif /* KING_H_ */
