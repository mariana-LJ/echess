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


vector<square> Pawn::getMoves(square & current, vector<vector<char> >& board){
  // No en passant or promotion considered yet
  vector<square> possibleMoves_;
  char color = (board[current.row][current.column] == 'P')? 'w': 'b';
  char pieceName = board[current.row][current.column];

  square destination1;
  square destination2;
  square destination3;
  square destination4;

  if(color == 'w'){
    if(current.column == 6){ // the first move for a white pawn
      if(board[current.column-1][current.row] == '.'){ // check if possible next square is empty
        destination1.column = current.column - 1;
        destination1.row = current.row;
        destination1.piece = pieceName;
        possibleMoves_.push_back(destination1);
      }
      if(board[current.column-2][current.row] == '.'){
        destination2.column = current.column - 2;
        destination2.row = current.row;
        destination2.piece = pieceName;
        possibleMoves_.push_back(destination2);
      }
    }
    else{ // after the first move for a white pawn
      destination1.column = current.column - 1;
      destination1.row = current.row;
      possibleMoves_.push_back(destination1);
    }
    if(current.column < 7 && current.row > 0){// check if white can take a black piece to the left
      if(board[current.column-1][current.row-1] > 'a'){
        destination3.column = current.column-1;
        destination3.row = current.row-1;
        destination3.piece = pieceName;
        possibleMoves_.push_back(destination3);
      }
    }
    if(current.column < 7 && current.row < 7){// check if white can take a black piece to the right
      if(board[current.column-1][current.row+1] > 'a'){
        destination4.column = current.column-1;
        destination4.row = current.row+1;
        destination4.piece = pieceName;
        possibleMoves_.push_back(destination4);
      }
    }
  }
  else{
    if(current.column == 1){ // the first move for a black pawn
      if(board[current.column-1][current.row] == '.'){ // check if possible next square is empty
        destination1.column = current.column + 1;
        destination1.row = current.row;
        destination1.piece = pieceName;
        possibleMoves_.push_back(destination1);
      }
      if(board[current.column-2][current.row] == '.'){
        destination2.column = current.column + 2;
        destination2.row = current.row;
        destination2.piece = pieceName;
        possibleMoves_.push_back(destination2);
      }
    }
    else{ // after the first move for a black pawn
      destination1.column = current.column + 1;
      destination1.row = current.row;
      possibleMoves_.push_back(destination1);
    }
    if(current.column > 0 && current.row < 7){// check if black can take a white piece to the right
      if(board[current.column+1][current.row+1] < 'a'){
        destination3.column = current.column+1;
        destination3.row = current.row+1;
        destination3.piece = pieceName;
        possibleMoves_.push_back(destination3);
      }
    }
      if(current.column < 7 && current.row > 0){// check if black can take a white piece to the left
        if(board[current.column+1][current.row-1] < 'a'){
          destination4.column = current.column+1;
          destination4.row = current.row-1;
          destination4.piece = pieceName;
          possibleMoves_.push_back(destination4);
        }
      }
  }
  return possibleMoves_;
}

