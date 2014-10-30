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
#include <sstream>
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
    moveNumber_ = 0;

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

// Verifies that the king of the opposite color was not left
// in check in the last movement
bool Board::wasKingLeftInCheck(){
    vector<movement> movements;

    for(int row = 0; row < rows_; ++row){
        for(int col = 0; col < columns_; ++col){
            movements = getMoves(row, col);

            for(vector<movement>::const_iterator p = movements.begin();
                p != movements.end(); ++p){
                if((board_[p->target_row][p->target_column] == 'K') ||
                   (board_[p->target_row][p->target_column] == 'k')){
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::isSameBoard(unsigned char (&shadowBoard)[8][8]){

    for(int row = 0; row < rows_; ++row){
        for(int col = 0; col < columns_; ++col){
            if((shadowBoard[row][col] == 0 && board_[row][col] != '.') ||
               (shadowBoard[row][col] == 1 && board_[row][col] == '.')){
                return false;
            }
        }
    }

    return true;
}

movement Board::findMovement(unsigned char (&shadowBoard)[8][8]){
    vector<movement> moves;

    for(int row = 0; row < rows_; ++row){
        for(int col = 0; col < columns_; ++col){
            moves = getMoves(row, col);
            for(vector<movement>::const_iterator p = moves.begin();
                p != moves.end(); ++p){
                Board clonBoard(*this);
                clonBoard.move(*p);
                if(!clonBoard.wasKingLeftInCheck() && clonBoard.isSameBoard(shadowBoard)){
                    return *p;
                }
            }
        }
    }

    movement emptyMove;
    return emptyMove;
}

vector<char> & Board::operator[](size_t index) {
  return board_[index];
}


void Board::printBoard(){
    for(int row = rows_- 1; row >= 0; --row){
        for(int col = 0; col < columns_; col++){
            cout << board_[row][col];
        }
    }
    cout << endl;
}


vector<movement> Board::getMoves(int row, int column){
    vector<movement> result;
    movement origin(row, column);

    if((whiteToMove_ && is_white(board_[origin.origin_row][origin.origin_column])) ||
       (!whiteToMove_ && is_black(board_[origin.origin_row][origin.origin_column]))){
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
        }
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

    // pre-en passant movement
    if(board_[move.origin_row][move.origin_column] == 'P' ||
       board_[move.origin_row][move.origin_column] == 'p'){
        if(move.target_row == enPassantRowCapture_ &&
           move.target_column == enPassantColumn_){
            board_[enPassantRow_][enPassantColumn_] = '.';
        }
    }

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

    // Update en passant
    if((board_[move.target_row][move.target_column] == 'P' ||
        board_[move.target_row][move.target_column] == 'p') &&
       abs(move.target_row - move.origin_row) == 2){
        enPassantColumn_ = move.target_column;
        enPassantRow_ = move.target_row;
        if(whiteToMove_){
            enPassantRowCapture_ = move.target_row - 1;
        }
        else{
            enPassantRowCapture_ = move.target_row + 1;
        }
    }
    else {
        enPassantRow_ = -1;
        enPassantColumn_ = -1;
        enPassantRowCapture_ = -1;
    }

    // update turn
    whiteToMove_ = !whiteToMove_;
    moveNumber_++;
}

string Board::FEN() {
    // board position
    int empty_spaces = 0;
    stringstream fen;
    for(int row = 7; row != -1; --row) {
      for(int column = 0; column != 8; ++column) {
        if(board_[row][column] == '.') {
          ++empty_spaces;
        } else {
          if(empty_spaces) {
            fen << empty_spaces;
            empty_spaces = 0;
          }
          fen << board_[row][column];
        }
      } // end of a row

      if(empty_spaces) {
        fen << empty_spaces;
        empty_spaces = 0;
      }
      if(row != 0) {
          fen << "/";
      }
    }

    // turn to move
    fen << (whiteToMove_? " w" : " b");

    // castling availability
    fen << " ";
    bool any_castle = false;
    if(whiteShortCastleAvailable_) {
      fen << "K";
      any_castle = true;
    }
    if(whiteLongCastleAvailable_) {
      fen << "Q";
      any_castle = true;
    }
    if(blackShortCastleAvailable_) {
      fen << "k";
      any_castle = true;
    }
    if(blackLongCastleAvailable_) {
      fen << "q";
      any_castle = true;
    }
    if(!any_castle) {
      fen << "-";
    }

    // en passant
    fen << " ";
    if(enPassantColumn_ != -1) {
      fen << enPassantColumn_;
      fen << enPassantRowCapture_;
    } else {
      fen << "-";
    }

    // halfmove clock
    fen << " ";
    fen << 0;

    // fullmove number
    fen << " ";
    fen << (moveNumber_/2)+1;

    return fen.str();
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
