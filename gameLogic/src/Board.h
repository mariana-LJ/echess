
#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "common.h"

class Board{
public:

    Board();
    void printBoard();
    std::vector<movement> getMoves(int row, int column);
    void move(movement move);

private:
    int rows_;
    int columns_;
    std::vector<std::vector<char> > board_;
    bool whiteShortCastleAvailable_;
    bool whiteLongCastleAvailable_;
    bool blackShortCastleAvailable_;
    bool blackLongCastleAvailable_;

    void initializeBoard();
};


#endif /* BOARD_H_ */
