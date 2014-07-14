/*
 * common.h
 *
 *  Created on: Jun 19, 2014
 *      Author: mlj
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <vector>

class Board;

struct movement {
  int origin_row;
  int origin_column;
  int target_row; // ranks: 1-8 -> representation: 0-7
  int target_column; // files: a=0, b=1,... h=7
  char piece; // the possible piece occupying a square

  movement() {
    origin_row = -1;
    origin_column = -1;
  }

  movement(int origin_row, int origin_column) {
    this->origin_row = origin_row;
    this->origin_column = origin_column;
  }

};


inline bool is_white(char c) {
  return (c >= 'A' && c <= 'Z');
}

inline bool is_black(char c) {
  return (c >= 'a' && c <= 'z');
}

void ValidateMove(movement & move, char color, Board& board, std::vector<movement> & possibleMoves);

#endif /* COMMON_H_ */
