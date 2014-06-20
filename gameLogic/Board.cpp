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
//#include <Pawn.h>
//#include <Knight.h>

using namespace std;

struct square{
	int file; // files: 1-8 -> representation: 0-7
	int rank; // ranks: a=0, b=1,... h=7
	char piece; // the possible piece occupying a square
};

class Pawn{
public:
	Pawn(){}
	Pawn(char piece){
		(piece == 'P')? color = 'w': color = 'b';
		pieceName_ = piece;

	}
	vector<square> getMoves(square current, vector<vector<char> >& board){ // No en passant or promotion considered yet
		square destination1;
		square destination2;
		square destination3;
		square destination4;

		if(color == 'w'){
			if(current.file == 6){ // the first move for a white pawn
				if(board[current.file-1][current.rank] == '.'){ // check if possible next square is empty
					destination1.file = current.file - 1;
					destination1.rank = current.rank;
					destination1.piece = pieceName_;
					possibleMoves_.push_back(destination1);
				}
				if(board[current.file-2][current.rank] == '.'){
					destination2.file = current.file - 2;
					destination2.rank = current.rank;
					destination2.piece = pieceName_;
					possibleMoves_.push_back(destination2);
				}
			}
			else{ // after the first move for a white pawn
				destination1.file = current.file - 1;
				destination1.rank = current.rank;
				possibleMoves_.push_back(destination1);
			}
			if(current.file < 7 && current.rank > 0){// check if white can take a black piece to the left
				if(board[current.file-1][current.rank-1] > 'a'){
					destination3.file = current.file-1;
					destination3.rank = current.rank-1;
					destination3.piece = pieceName_;
					possibleMoves_.push_back(destination3);
				}
			}
			if(current.file < 7 && current.rank < 7){// check if white can take a black piece to the right
				if(board[current.file-1][current.rank+1] > 'a'){
					destination4.file = current.file-1;
					destination4.rank = current.rank+1;
					destination4.piece = pieceName_;
					possibleMoves_.push_back(destination4);
				}
			}
		}
		else{
			if(current.file == 1){ // the first move for a black pawn
				if(board[current.file-1][current.rank] == '.'){ // check if possible next square is empty
					destination1.file = current.file + 1;
					destination1.rank = current.rank;
					destination1.piece = pieceName_;
					possibleMoves_.push_back(destination1);
				}
				if(board[current.file-2][current.rank] == '.'){
					destination2.file = current.file + 2;
					destination2.rank = current.rank;
					destination2.piece = pieceName_;
					possibleMoves_.push_back(destination2);
				}
			}
			else{ // after the first move for a black pawn
				destination1.file = current.file + 1;
				destination1.rank = current.rank;
				possibleMoves_.push_back(destination1);
			}
			if(current.file > 0 && current.rank < 7){// check if black can take a white piece to the right
				if(board[current.file+1][current.rank+1] < 'a'){
					destination3.file = current.file+1;
					destination3.rank = current.rank+1;
					destination3.piece = pieceName_;
					possibleMoves_.push_back(destination3);
				}
			}
				if(current.file < 7 && current.rank > 0){// check if black can take a white piece to the left
					if(board[current.file+1][current.rank-1] < 'a'){
						destination4.file = current.file+1;
						destination4.rank = current.rank-1;
						destination4.piece = pieceName_;
						possibleMoves_.push_back(destination4);
					}
				}
		}
		return possibleMoves_;
	}
private:
	vector<square> possibleMoves_;
	char color; // w=white, b=black;
	char pieceName_;
};

class Knight{
public:
	Knight(){}
	Knight(char piece){
		(piece == 'N')? color_ = 'w': color_ = 'b';
		pieceName_ = piece;
	}
	vector<square> getMoves(square current, vector<vector<char> >& board){
		square destination1;
		square destination2;
		square destination3;
		square destination4;
		square destination5;
		square destination6;
		square destination7;
		square destination8;

		if(current.rank >= 0 && current.rank < 6){
			destination1.rank = current.rank + 2; // 2 places right
			destination2.rank = current.rank + 2;
			if(current.file > 0){
				destination1.file = current.file - 1; // 1 place up
				destination1.piece = pieceName_;

				if(board[destination1.rank][destination1.file] == '.' ){
					possibleMoves_.push_back(destination1);
				}
				else if(color_ == 'w' && board[destination1.rank][destination1.file] > 'a'){
					possibleMoves_.push_back(destination1);
				}
				else if(color_ == 'b' && board[destination1.rank][destination1.file] < 'a'){
					possibleMoves_.push_back(destination1);
				}
			}
			else if(current.file < 7){
				destination2.file = current.file + 1; // 1 place down
				destination2.piece = pieceName_;

				if(board[destination2.rank][destination2.file] == '.'){
					possibleMoves_.push_back(destination2);
				}
				else if(color_ == 'w' && board[destination2.rank][destination2.file] > 'a'){
					possibleMoves_.push_back(destination2);
				}
				else if(color_ == 'b' && board[destination2.rank][destination2.file] < 'a'){
					possibleMoves_.push_back(destination2);
				}
			}
		}
		else if(current.file <= 7 && current.file > 1){
			destination3.file = current.file - 2; // 2 places up
			destination4.file = current.file - 2;
			if(current.rank < 7){
				destination3.rank = current.rank + 1; // 1 place right
				destination3.piece = pieceName_;

				if(board[destination3.rank][destination3.file] == '.'){
					possibleMoves_.push_back(destination3);
				}
				else if(color_ == 'w' && board[destination3.rank][destination3.file] > 'a'){
					possibleMoves_.push_back(destination3);
				}
				else if(color_ == 'b' && board[destination3.rank][destination3.file] < 'a'){
					possibleMoves_.push_back(destination3);
				}
			}
			else if(current.rank > 0){
				destination4.rank = current.rank - 1; // 1 place left
				destination4.piece = pieceName_;

				if(board[destination4.rank][destination4.file] == '.'){
					possibleMoves_.push_back(destination4);
				}
				else if(color_ == 'w' && board[destination4.rank][destination4.file] > 'a'){
					possibleMoves_.push_back(destination4);
				}
				else if(color_ == 'b' && board[destination4.rank][destination4.file] < 'a'){
					possibleMoves_.push_back(destination4);
				}
			}
		}
		else if(current.rank > 1 && current.rank <= 7){
			destination5.rank = current.rank - 2; // 2 places to the left
			destination6.rank = current.rank - 2;
			if(current.file > 0){
				destination5.file = current.file - 1; // 1 place up
				destination5.piece = pieceName_;

				if(board[destination5.rank][destination5.file] == '.'){
					possibleMoves_.push_back(destination5);
				}
				else if(color_ == 'w' && board[destination5.rank][destination5.file] > 'a'){
					possibleMoves_.push_back(destination5);
				}
				else if(color_ == 'b' && board[destination5.rank][destination5.file] < 'a'){
					possibleMoves_.push_back(destination5);
				}

			}
			else if(current.file < 7){
				destination6.file = current.file + 1; // 1 place down
				destination6.piece = pieceName_;

				if(board[destination6.rank][destination6.file] == '.'){
					possibleMoves_.push_back(destination6);
				}
				else if(color_ == 'w' && board[destination6.rank][destination6.file] > 'a'){
					possibleMoves_.push_back(destination6);
				}
				else if(color_ == 'b' && board[destination6.rank][destination6.file] < 'a'){
					possibleMoves_.push_back(destination6);
				}
			}
		}
		else if(current.file >= 0 && current.file < 6){
			destination7.file = current.file + 2; // 2 places down
			destination8.file = current.file + 2;
			if(current.rank < 7){
				destination7.rank = current.rank + 1; // 1 place right
				destination7.piece = pieceName_;

				if(board[destination7.rank][destination7.file] == '.'){
					possibleMoves_.push_back(destination7);
				}
				else if(color_ == 'w' && board[destination7.rank][destination7.file] > 'a'){
					possibleMoves_.push_back(destination7);
				}
				else if(color_ == 'b' && board[destination7.rank][destination7.file] < 'a'){
					possibleMoves_.push_back(destination7);
				}
			}
			else if(current.rank > 0){
				destination8.rank = current.rank - 1; // 1 place left
				destination8.piece = pieceName_;

				if(board[destination8.rank][destination8.file] == '.'){
					possibleMoves_.push_back(destination8);
				}
				else if(color_ == 'w' && board[destination8.rank][destination8.file] > 'a'){
					possibleMoves_.push_back(destination8);
				}
				else if(color_ == 'b' && board[destination8.rank][destination8.file] < 'a'){
					possibleMoves_.push_back(destination8);
				}
			}
		}

		return possibleMoves_;
	}
private:
	vector<square> possibleMoves_;
	char color_; // w=white, b=black
	char pieceName_;
};

class Board{
public:
	Pawn whitePawn_;
	Pawn blackPawn_;
	Knight whiteKnight_;
	Knight blackKnight_;

	Board(){
		initializeBoard();
		printBoard();
	}

	void printBoard(){
		for(int row = 0; row < rows_; row++){
			for(int col = 0; col < columns_; col++){
				printf("%c\t", board_[row][col]);
			}
			printf("\n");
		}
	}

	vector<square> getMoves(square origin){
		char piece = board_[origin.file][origin.rank];
		switch(piece){
		case ('P'):
				possibleMoves_ = whitePawn_.getMoves(origin, board_);
				break;
		case('p'):
				possibleMoves_ = blackPawn_.getMoves(origin, board_);
				break;
		case('n'):
				possibleMoves_ = blackKnight_.getMoves(origin, board_);
				break;
		case ('N'):
				possibleMoves_ = whiteKnight_.getMoves(origin, board_);
				break;
		default:
				printf("Invalid move.\n");
			break;
		}

		return possibleMoves_;
	}

private:
	const int rows_ = 8;
	const int columns_ = 8;
	vector<vector<char> > board_;
	vector<square> possibleMoves_;

	void initializeBoard(){

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
			board_[7][col] = 'p';
		}

		for(int row = 2; row < 6; row++){
			for(int col = 0; col< columns_; col++){
				board_[row][col] = '.';
			}
		}
	}
};

int main(void){
	Board b();

}
