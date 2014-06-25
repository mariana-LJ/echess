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

vector<movement> Knight::getMoves(movement & current, vector<vector<char> >& board){
  vector<movement> possibleMoves_;
  char color = (board[current.target_row][current.target_column] == 'N')? 'w': 'b';
  char pieceName = board[current.target_row][current.target_column];

  movement destination1;
  movement destination2;
  movement destination3;
  movement destination4;
  movement destination5;
  movement destination6;
  movement destination7;
  movement destination8;

  if(current.target_column >= 0 && current.target_column < 6){
    destination1.target_column = current.target_column + 2; // 2 places right
    destination2.target_column = current.target_column + 2;
    if(current.target_row > 0){
      destination1.target_row = current.target_row - 1; // 1 place up
      destination1.piece = board[destination1.target_row][destination1.target_column];

      if(destination1.piece == '.' ){
        possibleMoves_.push_back(destination1);
      }
      else if((color == 'w' && destination1.piece > 'a') ||
    		  (color == 'b' && destination1.piece < 'a')){
        possibleMoves_.push_back(destination1);
      }
    }
    if(current.target_row < 7){
      destination2.target_row = current.target_row + 1; // 1 place down
      destination2.piece = board[destination2.target_row][destination2.target_column];

      if(destination2.piece == '.'){
        possibleMoves_.push_back(destination2);
      }
      else if((color == 'w' && destination2.piece > 'a') ||
    		  (color == 'b' && destination2.piece < 'a')){
        possibleMoves_.push_back(destination2);
      }
    }
  }
  if(current.target_row <= 7 && current.target_row > 1){
    destination3.target_row = current.target_row - 2; // 2 places up
    destination4.target_row = current.target_row - 2;
    if(current.target_column < 7){
      destination3.target_column = current.target_column + 1; // 1 place right
      destination3.piece = board[destination3.target_row][destination3.target_column];

      if(destination3.piece == '.'){
        possibleMoves_.push_back(destination3);
      }
      else if((color == 'w' && destination3.piece > 'a') ||
    		  (color == 'b' && destination3.piece < 'a')){
        possibleMoves_.push_back(destination3);
      }
    }
    if(current.target_column > 0){
      destination4.target_column = current.target_column - 1; // 1 place left
      destination4.piece = board[destination4.target_row][destination4.target_column];

      if(destination4.piece == '.'){
        possibleMoves_.push_back(destination4);
      }
      else if((color == 'w' && destination4.piece > 'a') ||
    		  (color == 'b' && destination4.piece < 'a')){
        possibleMoves_.push_back(destination4);
      }
    }
  }
  if(current.target_column > 1 && current.target_column <= 7){
    destination5.target_column = current.target_column - 2; // 2 places to the left
    destination6.target_column = current.target_column - 2;
    if(current.target_row > 0){
      destination5.target_row = current.target_row - 1; // 1 place up
      destination5.piece = board[destination5.target_row][destination5.target_column];

      if(destination5.piece == '.'){
        possibleMoves_.push_back(destination5);
      }
      else if((color == 'w' && destination5.piece > 'a') ||
    		  (color == 'b' && destination5.piece < 'a')){
        possibleMoves_.push_back(destination5);
      }
    }
    if(current.target_row < 7){
      destination6.target_row = current.target_row + 1; // 1 place down
      destination6.piece = board[destination6.target_row][destination6.target_column];

      if(destination6.piece == '.'){
        possibleMoves_.push_back(destination6);
      }
      else if((color == 'w' && destination6.piece > 'a') ||
    		  (color == 'b' && destination6.piece < 'a')){
        possibleMoves_.push_back(destination6);
      }
    }
  }
  if(current.target_row >= 0 && current.target_row < 6){
    destination7.target_row = current.target_row + 2; // 2 places down
    destination8.target_row = current.target_row + 2;
    if(current.target_column < 7){
      destination7.target_column = current.target_column + 1; // 1 place right
      destination7.piece = board[destination7.target_row][destination7.target_column];

      if(destination7.piece == '.'){
        possibleMoves_.push_back(destination7);
      }
      else if((color == 'w' && destination7.piece > 'a') ||
    		  (color == 'b' && destination7.piece < 'a')){
        possibleMoves_.push_back(destination7);
      }
    }
    if(current.target_column > 0){
      destination8.target_column = current.target_column - 1; // 1 place left
      destination8.piece = board[destination8.target_row][destination8.target_column];

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
