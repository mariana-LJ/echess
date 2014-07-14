/*
 * board.cpp
 *
 *  Created on: May 23, 2014
 *      Author: mlj
 */


#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace std;

Board::Board(){
    initializeBoard();
}

void Board::initializeBoard(){
    rows_ = 8;
    columns_ = 8;
    whiteShortCastleAvailable_ = true;
    whiteLongCastleAvailable_ = true;
    blackShortCastleAvailable_ = true;
    blackLongCastleAvailable_ = true;
    whiteToMove_ = true;
    enPassantColumn_ = -1;
    enPassantRow_ = -1;
    enPassantRowCapture_ = -1;

    // initialize vector
    board_.resize(rows_);
    for(int i=0; i < rows_; ++i) {
        board_[i].resize(columns_);
    }

    board_[0][0] = 'R';
    board_[0][1] = 'N';
    board_[0][2] = 'B';
    board_[0][3] = 'Q';
    board_[0][4] = 'K';
    board_[0][5] = 'B';
    board_[0][6] = 'N';
    board_[0][7] = 'R';

    board_[7][0] = 'r';
    board_[7][1] = 'n';
    board_[7][2] = 'b';
    board_[7][3] = 'q';
    board_[7][4] = 'k';
    board_[7][5] = 'b';
    board_[7][6] = 'n';
    board_[7][7] = 'r';

    for(int col = 0; col < columns_; col++){
        board_[1][col] = 'P';
        board_[6][col] = 'p';
    }

    for(int row = 2; row < 6; row++){
        for(int col = 0; col< columns_; col++){
            board_[row][col] = '.';
        }
    }
}


vector<char> & Board::operator[](size_t index) {
  return board_[index];
}


void Board::printBoard(){
    for(int row = rows_- 1; row >= 0; --row){
        for(int col = 0; col < columns_; col++){
            cout << board_[row][col] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

vector<movement> Board::getMoves(int row, int column){
    vector<movement> result;
    movement origin(row, column);

    switch(board_[origin.origin_row][origin.origin_column]){
        case ('P'):
        case('p'):
              result = Pawn::getMoves(origin, *this);
          break;
        case ('N'):
        case('n'):
            result = Knight::getMoves(origin, *this);
          break;
        case('B'):
        case('b'):
          result = Bishop::getMoves(origin, *this);
          break;
        case('R'):
        case('r'):
          result = Rook::getMoves(origin, *this);
          break;
        case('Q'):
        case('q'):
          result = Queen::getMoves(origin, *this);
          break;
        case('K'):
        case('k'):
          result = King::getMoves(origin, *this);
          break;
        default:
            printf("Invalid move.\n");
          break;
    }

    return result;
}


void Board::move(movement move) {
    // pre-castle rook movement
    if(board_[move.origin_row][move.origin_column] == 'K' ||
       board_[move.origin_row][move.origin_column] == 'k'){ // king
        // just move the rook, the king is moved in the common code below
        if(move.target_column == (move.origin_column + 2)){  // King's side castle
           board_[move.origin_row][move.origin_column + 1] = board_[move.origin_row][7];
           board_[move.origin_row][7] = '.';
        }
        else if(move.target_column == (move.origin_column - 2)){ // or Queen's side castle
              board_[move.origin_row][move.origin_column - 1] = board_[move.origin_row][0];
              board_[move.origin_row][0] = '.';
        }
    }

    // TODO pre-en passant movement

    board_[move.target_row][move.target_column] = board_[move.origin_row][move.origin_column];
    board_[move.origin_row][move.origin_column] = '.';

    // update castle availability
    if(board_[move.target_row][move.target_column] == 'K') {
        whiteShortCastleAvailable_ = false;
        whiteLongCastleAvailable_ = false;
    }
    else if(board_[move.target_row][move.target_column] == 'k') {
        blackShortCastleAvailable_ = false;
        blackLongCastleAvailable_ = false;
    }
    else if(board_[move.target_row][move.target_column] == 'R' && move.origin_row == 0){
        if(move.origin_column == 7){
            whiteShortCastleAvailable_ = false;
        }
        else if(move.origin_column == 0){
            whiteLongCastleAvailable_ = false;
        }
    }
    else if(board_[move.target_row][move.target_column] == 'r' && move.origin_row == 7){
        if(move.origin_column == 7){
            blackShortCastleAvailable_ = false;
        }
        else if(move.origin_column == 0){
            blackLongCastleAvailable_ = false;
        }
    }

    // TODO update en passant

}

/*int main(void){
	Board b;
	square s;
	s.row = 0;
	s.column = 1;
	vector<square> m = b.getMoves(s);
	cout << endl;
	cout << "Possible moves: " << endl;
	for(vector<square>::iterator it = m.begin(); it != m.end(); ++it) {
	  cout << it->row << "," << it->column << endl;
	}
}
*/
