/*
 *  Created on: Oct 26, 2014
 *      Author: Mariana Lopez Jaimez
 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <string>

#include "Board.h"

typedef unsigned char byte;
using namespace std;

void PrintShadowBoard(byte *array) {
    // need to print from black perspective to match board.PrintBoard
    // put pointer to last row
    array += 7*8;
    for(int r = 7; r >= 0; --r) {
        for(int c = 0; c < 8; ++c) {
            cout << (*array ? 1 : 0 );
            array++;
        }
        // here the pointer is at the end of the current row
        // -8 returns to the beginning of the row
        // -16 goes to the beginning of the previous row
        array -= 16;
    }
    cout << endl;
}


void ChessPi(){
    byte board[8][8];
    byte *first = &(board[0][0]);
    Board b;
    movement m;

    memset(first, 1, 16);
    memset(first+16, 0, 32);
    memset(first+48, 1, 16);

    b.printBoard();
    PrintShadowBoard(first);
    sleep(2);

    board[1][4] = 0;
    board[3][4] = 1;
    m = b.findMovement(board);
    b.move(m);
    b.printBoard();
    PrintShadowBoard(first);
    sleep(2);

    board[7][6] = 0;
    board[5][6] = 1;
    m = b.findMovement(board);
    if(m.origin_row != -1 && m.origin_column != -1 &&
       m.target_row != -1 && m.target_column != -1){
        b.move(m);
    }
    b.printBoard();
    PrintShadowBoard(first);
    sleep(2);

    board[7][6] = 1;
    board[5][6] = 0;
    board[6][6] = 0;
    board[5][5] = 1;
    m = b.findMovement(board);
    if(m.origin_row != -1 && m.origin_column != -1 &&
       m.target_row != -1 && m.target_column != -1){
        b.move(m);
    }
    b.printBoard();
    PrintShadowBoard(first);
    sleep(2);

    cout << "exit" << endl;

}

int main(int argc, char **argv){
  ChessPi();
  return 0;
}
