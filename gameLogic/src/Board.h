/*
 * board.h
 *
 *  Created on: May 23, 2014
 *      Author: mlj
 */

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
    std::vector<char> & operator[](std::size_t index);
    bool whiteShortCastleAvailable() { return whiteShortCastleAvailable_; }
    bool whiteLongCastleAvailable() { return whiteLongCastleAvailable_; }
    bool blackShortCastleAvailable() { return blackShortCastleAvailable_; }
    bool blackLongCastleAvailable() { return blackLongCastleAvailable_; }
    void setEnPassantColumn(int c){ enPassantColumn_ = c; }
    void setEnPassantRow(int r){ enPassantRow_ = r;}
    void setEnPassantRowCapture(int rc){ enPassantRowCapture_ = rc; }
    int getEnPassantColumn(){return enPassantColumn_; }
    int getEnPassantRow(){return enPassantRow_; }
    int getEnPassantRowCapture(){return enPassantRowCapture_; }
    movement findMove(unsigned char (&shadowBoard)[8][8]);

private:
    int rows_;
    int columns_;
    std::vector<std::vector<char> > board_;
    bool whiteShortCastleAvailable_;
    bool whiteLongCastleAvailable_;
    bool blackShortCastleAvailable_;
    bool blackLongCastleAvailable_;
    bool whiteToMove_;
    int enPassantColumn_;
    int enPassantRow_;
    int enPassantRowCapture_;

    void initializeBoard();
    bool wasKingLeftInCheck();
    bool isSameBoard(unsigned char (&shadowBoard)[8][8]);
};


#endif /* BOARD_H_ */
