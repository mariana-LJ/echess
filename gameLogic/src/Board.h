/*
 * board.h
 *
 *  Created on: May 23, 2014
 *      Author: mlj
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <string>
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
    int getEnPassantColumn(){return enPassantColumn_; }
    int getEnPassantRow(){return enPassantRow_; }
    int getEnPassantRowCapture(){return enPassantRowCapture_; }
    bool wasKingLeftInCheck();
    std::vector<movement> findMovement(unsigned char (&shadowBoard)[8][8]);
    std::string FEN();
    bool whiteToMove() { return whiteToMove_; }

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
    int moveNumber_;

    void initializeBoard();
    bool isSameBoard(unsigned char (&shadowBoard)[8][8]);
};


#endif /* BOARD_H_ */
