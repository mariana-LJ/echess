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

void PrintBoard(byte *array) {
    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            cout << (*array ? 1 : 0 )<< " ";
            array++;
        }
        cout << endl;
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
    board[1][4] = 0;
    board[3][4] = 1;
    m = b.findMovement(board);
    b.move(m);
    b.printBoard();

    cout << "exit" << endl;
}

int main(int argc, char **argv){
  ChessPi();
  return 0;
}
