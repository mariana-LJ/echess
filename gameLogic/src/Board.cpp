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
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"

using namespace std;

class Board{
public:

	Board(){
		initializeBoard();
		printBoard();
	}

	void printBoard(){
		for(int row = rows_- 1; row >= 0; --row){
			for(int col = 0; col < columns_; col++){
				printf("%c\t", board_[row][col]);
			}
			printf("\n");
		}
	}

	vector<square> getMoves(square origin){
	vector<square> result;

	switch(board_[origin.row][origin.column]){
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

private:
	int rows_;
	int columns_;
	vector<vector<char> > board_;

	void initializeBoard(){
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
};

int main(void){
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
