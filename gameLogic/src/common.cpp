#include "common.h"
#include "Board.h"

using namespace std;

void ValidateMove(movement & move, char color, Board& board, std::vector<movement> & possibleMoves){
    if(move.target_row >= 0 && move.target_row <= 7 &&
       move.target_column >= 0 && move.target_column <= 7) {
        if(board[move.target_row][move.target_column] == '.' ){
            possibleMoves.push_back(move);
        }
        else if((color == 'w' && is_black(board[move.target_row][move.target_column])) ||
                (color == 'b' && is_white(board[move.target_row][move.target_column]))){
            possibleMoves.push_back(move);
        }
    }
}
