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

using namespace std;

Board::Board(){
  initializeBoard();
}

void Board::printBoard(){
  for(int row = rows_- 1; row >= 0; --row){
    for(int col = 0; col < columns_; col++){
      printf("%c\t", board_[row][col]);
    }
    printf("\n");
  }
}

vector<movement> Board::getMoves(int row, int column){
  vector<movement> result;
  movement origin(row, column);

  switch(board_[origin.origin_row][origin.origin_column]){
    case ('P'):
    case('p'):
          result = Pawn::getMoves(origin, board_);
      break;
    case ('N'):
    case('n'):
        result = Knight::getMoves(origin, board_);
      break;
    case('B'):
    case('b'):
      result = Bishop::getMoves(origin, board_);
      break;
    case('R'):
    case('r'):
      result = Rook::getMoves(origin, board_);
      break;
    default:
        printf("Invalid move.\n");
      break;
  }

  return result;
}

void Board::initializeBoard(){
  rows_ = 8;
  columns_ = 8;

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

void Board::move(movement move) {
  board_[move.target_row][move.target_column] = board_[move.origin_row][move.origin_column];
  board_[move.origin_row][move.origin_column] = '.';
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
