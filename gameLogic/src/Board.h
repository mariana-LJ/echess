
#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "common.h"

class Board{
public:

  Board();
  void printBoard();
  std::vector<square> getMoves(square origin);

private:
  int rows_;
  int columns_;
  std::vector<std::vector<char> > board_;

  void initializeBoard();
};


#endif /* BOARD_H_ */
