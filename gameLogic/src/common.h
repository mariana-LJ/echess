/*
 * common.h
 *
 *  Created on: Jun 19, 2014
 *      Author: acp
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <vector>

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

inline void ValidateMove(movement & move, char color, std::vector<std::vector<char> >& board, std::vector<movement> & possibleMoves){
    if(move.target_row >= 0 && move.target_row <= 7 &&
       move.target_column >= 0 && move.target_column <= 7) {
        if(board[move.target_row][move.target_column] == '.' ){
            possibleMoves.push_back(move);
        }
        else if((color == 'w' && is_black(board[move.target_row][move.target_column])) ||
                (color == 'b' && is_white(board[move.target_row][move.target_column]))){
            possibleMoves.push_back(move);
        }
    }
}

#endif /* COMMON_H_ */
