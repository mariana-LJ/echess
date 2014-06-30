/*
 * Pawn.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: acp
 */

#include "Pawn.h"

using namespace std;

Pawn::Pawn() {
  // TODO Auto-generated constructor stub

}

Pawn::~Pawn() {
  // TODO Auto-generated destructor stub
}


vector<movement> Pawn::getMoves(movement & current, vector<vector<char> >& board){
  // No en passant or promotion considered yet
  vector<movement> possibleMoves_;
  char color = (board[current.origin_row][current.origin_column] == 'P')? 'w': 'b';
  char pieceName = board[current.origin_row][current.origin_column];

  movement destination1(current);
  movement destination2(current);
  movement destination3(current);
  movement destination4(current);

  if(color == 'w'){
    if(current.origin_row == 1){ // the first move for a white pawn
      if(board[current.origin_row+1][current.origin_column] == '.'){ // check if possible next square is empty
        destination1.target_row = current.origin_row + 1;
        destination1.target_column = current.origin_column;
        destination1.piece = pieceName;
        possibleMoves_.push_back(destination1);

        if(board[current.origin_row+2][current.origin_column] == '.'){ // check two squares ahead
        	destination2.target_row = current.origin_row + 2;
            destination2.target_column = current.origin_column;
            destination2.piece = pieceName;
            possibleMoves_.push_back(destination2);
        }
      }
    }
    else if(current.origin_row < 7){ // after the first move for a white pawn
      if(board[current.origin_row+1][current.origin_column] == '.'){
    	  destination1.target_row = current.origin_row + 1;
    	  destination1.target_column = current.origin_column;
    	  possibleMoves_.push_back(destination1);
      }
    }
    if(current.origin_row < 7 && current.origin_column > 0){// check if white can take a black piece to the left
      if(is_black(board[current.origin_row+1][current.origin_column-1])){
    	destination3.target_row = current.origin_row+1;
    	destination3.target_column = current.origin_column-1;
        destination3.piece = pieceName;
        possibleMoves_.push_back(destination3);
      }
    }
    if(current.origin_row < 7 && current.origin_column > 7){// check if white can take a black piece to the right
      if(is_black(board[current.origin_row+1][current.origin_column+1])){
    	destination4.target_row = current.origin_row+1;
    	destination4.target_column = current.origin_column+1;
        destination4.piece = pieceName;
        possibleMoves_.push_back(destination4);
      }
    }
  }
  else{
    if(current.origin_row == 6){ // the first move for a black pawn
      if(board[current.origin_row-1][current.origin_column] == '.'){ // check if possible next square is empty
    	  destination1.target_row = current.origin_row - 1;
    	  destination1.target_column = current.origin_column;
    	  destination1.piece = pieceName;
    	  possibleMoves_.push_back(destination1);

    	  if(board[current.origin_row-2][current.origin_column] == '.'){
    		  destination2.target_row = current.origin_row - 2;
    		  destination2.target_column = current.origin_column;
    		  destination2.piece = pieceName;
    		  possibleMoves_.push_back(destination2);
    	  }
      }
    }
    else if(current.origin_row > 0){ // after the first move for a black pawn
    	if(board[current.origin_row-1][current.origin_column] == '.'){
    		destination1.target_row = current.origin_row - 1;
    		destination1.target_column = current.origin_column;
    		possibleMoves_.push_back(destination1);
    	}
    }
    if(current.origin_row > 0 && current.origin_column < 7){// check if black can take a white piece to the right
      if(is_white(board[current.origin_row-1][current.origin_column+1])){
    	destination3.target_row = current.origin_row-1;
    	destination3.target_column = current.origin_column+1;
        destination3.piece = pieceName;
        possibleMoves_.push_back(destination3);
      }
    }
      if(current.origin_row > 0 && current.origin_column > 0){// check if black can take a white piece to the left
        if(is_white(board[current.origin_row-1][current.origin_column-1])){
          destination4.target_row = current.origin_row-1;
          destination4.target_column = current.origin_column-1;
          destination4.piece = pieceName;
          possibleMoves_.push_back(destination4);
        }
      }
  }
  return possibleMoves_;
}

