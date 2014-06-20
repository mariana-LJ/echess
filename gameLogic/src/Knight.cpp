/*
 * Knight.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: acp
 */

#include "Knight.h"

using namespace std;

Knight::Knight() {
  // TODO Auto-generated constructor stub

}

Knight::~Knight() {
  // TODO Auto-generated destructor stub
}

vector<square> Knight::getMoves(square & current, vector<vector<char> >& board){
  vector<square> possibleMoves_;
  char color = (board[current.row][current.column] == 'N')? 'w': 'b';
  char pieceName = board[current.row][current.column];

  square destination1;
  square destination2;
  square destination3;
  square destination4;
  square destination5;
  square destination6;
  square destination7;
  square destination8;

  if(current.row >= 0 && current.row < 6){
    destination1.row = current.row + 2; // 2 places right
    destination2.row = current.row + 2;
    if(current.column > 0){
      destination1.column = current.column - 1; // 1 place up
      destination1.piece = pieceName;

      if(board[destination1.row][destination1.column] == '.' ){
        possibleMoves_.push_back(destination1);
      }
      else if(color == 'w' && board[destination1.row][destination1.column] > 'a'){
        possibleMoves_.push_back(destination1);
      }
      else if(color == 'b' && board[destination1.row][destination1.column] < 'a'){
        possibleMoves_.push_back(destination1);
      }
    }
    else if(current.column < 7){
      destination2.column = current.column + 1; // 1 place down
      destination2.piece = pieceName;

      if(board[destination2.row][destination2.column] == '.'){
        possibleMoves_.push_back(destination2);
      }
      else if(color == 'w' && board[destination2.row][destination2.column] > 'a'){
        possibleMoves_.push_back(destination2);
      }
      else if(color == 'b' && board[destination2.row][destination2.column] < 'a'){
        possibleMoves_.push_back(destination2);
      }
    }
  }
  else if(current.column <= 7 && current.column > 1){
    destination3.column = current.column - 2; // 2 places up
    destination4.column = current.column - 2;
    if(current.row < 7){
      destination3.row = current.row + 1; // 1 place right
      destination3.piece = pieceName;

      if(board[destination3.row][destination3.column] == '.'){
        possibleMoves_.push_back(destination3);
      }
      else if(color == 'w' && board[destination3.row][destination3.column] > 'a'){
        possibleMoves_.push_back(destination3);
      }
      else if(color == 'b' && board[destination3.row][destination3.column] < 'a'){
        possibleMoves_.push_back(destination3);
      }
    }
    else if(current.row > 0){
      destination4.row = current.row - 1; // 1 place left
      destination4.piece = pieceName;

      if(board[destination4.row][destination4.column] == '.'){
        possibleMoves_.push_back(destination4);
      }
      else if(color == 'w' && board[destination4.row][destination4.column] > 'a'){
        possibleMoves_.push_back(destination4);
      }
      else if(color == 'b' && board[destination4.row][destination4.column] < 'a'){
        possibleMoves_.push_back(destination4);
      }
    }
  }
  else if(current.row > 1 && current.row <= 7){
    destination5.row = current.row - 2; // 2 places to the left
    destination6.row = current.row - 2;
    if(current.column > 0){
      destination5.column = current.column - 1; // 1 place up
      destination5.piece = pieceName;

      if(board[destination5.row][destination5.column] == '.'){
        possibleMoves_.push_back(destination5);
      }
      else if(color == 'w' && board[destination5.row][destination5.column] > 'a'){
        possibleMoves_.push_back(destination5);
      }
      else if(color == 'b' && board[destination5.row][destination5.column] < 'a'){
        possibleMoves_.push_back(destination5);
      }

    }
    else if(current.column < 7){
      destination6.column = current.column + 1; // 1 place down
      destination6.piece = pieceName;

      if(board[destination6.row][destination6.column] == '.'){
        possibleMoves_.push_back(destination6);
      }
      else if(color == 'w' && board[destination6.row][destination6.column] > 'a'){
        possibleMoves_.push_back(destination6);
      }
      else if(color == 'b' && board[destination6.row][destination6.column] < 'a'){
        possibleMoves_.push_back(destination6);
      }
    }
  }
  else if(current.column >= 0 && current.column < 6){
    destination7.column = current.column + 2; // 2 places down
    destination8.column = current.column + 2;
    if(current.row < 7){
      destination7.row = current.row + 1; // 1 place right
      destination7.piece = pieceName;

      if(board[destination7.row][destination7.column] == '.'){
        possibleMoves_.push_back(destination7);
      }
      else if(color == 'w' && board[destination7.row][destination7.column] > 'a'){
        possibleMoves_.push_back(destination7);
      }
      else if(color == 'b' && board[destination7.row][destination7.column] < 'a'){
        possibleMoves_.push_back(destination7);
      }
    }
    else if(current.row > 0){
      destination8.row = current.row - 1; // 1 place left
      destination8.piece = pieceName;

      if(board[destination8.row][destination8.column] == '.'){
        possibleMoves_.push_back(destination8);
      }
      else if(color == 'w' && board[destination8.row][destination8.column] > 'a'){
        possibleMoves_.push_back(destination8);
      }
      else if(color == 'b' && board[destination8.row][destination8.column] < 'a'){
        possibleMoves_.push_back(destination8);
      }
    }
  }

  return possibleMoves_;
}
