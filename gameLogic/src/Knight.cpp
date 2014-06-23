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

  if(current.column >= 0 && current.column < 6){
    destination1.column = current.column + 2; // 2 places right
    destination2.column = current.column + 2;
    if(current.row > 0){
      destination1.row = current.row - 1; // 1 place up
      destination1.piece = board[destination1.row][destination1.column];

      if(destination1.piece == '.' ){
        possibleMoves_.push_back(destination1);
      }
      else if((color == 'w' && destination1.piece > 'a') ||
    		  (color == 'b' && destination1.piece < 'a')){
        possibleMoves_.push_back(destination1);
      }
    }
    if(current.row < 7){
      destination2.row = current.row + 1; // 1 place down
      destination2.piece = board[destination2.row][destination2.column];

      if(destination2.piece == '.'){
        possibleMoves_.push_back(destination2);
      }
      else if((color == 'w' && destination2.piece > 'a') ||
    		  (color == 'b' && destination2.piece < 'a')){
        possibleMoves_.push_back(destination2);
      }
    }
  }
  if(current.row <= 7 && current.row > 1){
    destination3.row = current.row - 2; // 2 places up
    destination4.row = current.row - 2;
    if(current.column < 7){
      destination3.column = current.column + 1; // 1 place right
      destination3.piece = board[destination3.row][destination3.column];

      if(destination3.piece == '.'){
        possibleMoves_.push_back(destination3);
      }
      else if((color == 'w' && destination3.piece > 'a') ||
    		  (color == 'b' && destination3.piece < 'a')){
        possibleMoves_.push_back(destination3);
      }
    }
    if(current.column > 0){
      destination4.column = current.column - 1; // 1 place left
      destination4.piece = board[destination4.row][destination4.column];

      if(destination4.piece == '.'){
        possibleMoves_.push_back(destination4);
      }
      else if((color == 'w' && destination4.piece > 'a') ||
    		  (color == 'b' && destination4.piece < 'a')){
        possibleMoves_.push_back(destination4);
      }
    }
  }
  if(current.column > 1 && current.column <= 7){
    destination5.column = current.column - 2; // 2 places to the left
    destination6.column = current.column - 2;
    if(current.row > 0){
      destination5.row = current.row - 1; // 1 place up
      destination5.piece = board[destination5.row][destination5.column];

      if(destination5.piece == '.'){
        possibleMoves_.push_back(destination5);
      }
      else if((color == 'w' && destination5.piece > 'a') ||
    		  (color == 'b' && destination5.piece < 'a')){
        possibleMoves_.push_back(destination5);
      }
    }
    if(current.row < 7){
      destination6.row = current.row + 1; // 1 place down
      destination6.piece = board[destination6.row][destination6.column];

      if(destination6.piece == '.'){
        possibleMoves_.push_back(destination6);
      }
      else if((color == 'w' && destination6.piece > 'a') ||
    		  (color == 'b' && destination6.piece < 'a')){
        possibleMoves_.push_back(destination6);
      }
    }
  }
  if(current.row >= 0 && current.row < 6){
    destination7.row = current.row + 2; // 2 places down
    destination8.row = current.row + 2;
    if(current.column < 7){
      destination7.column = current.column + 1; // 1 place right
      destination7.piece = board[destination7.row][destination7.column];

      if(destination7.piece == '.'){
        possibleMoves_.push_back(destination7);
      }
      else if((color == 'w' && destination7.piece > 'a') ||
    		  (color == 'b' && destination7.piece < 'a')){
        possibleMoves_.push_back(destination7);
      }
    }
    if(current.column > 0){
      destination8.column = current.column - 1; // 1 place left
      destination8.piece = board[destination8.row][destination8.column];

      if(destination8.piece == '.'){
        possibleMoves_.push_back(destination8);
      }
      else if((color == 'w' && destination8.piece > 'a') ||
    		  (color == 'b' && destination8.piece < 'a')){
        possibleMoves_.push_back(destination8);
      }
    }
  }

  return possibleMoves_;
}
