/*
 *  Created on: Mar 16, 2014
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
#include "PiTFTButton.h"

typedef unsigned char byte;
using namespace std;

class A2D_Converter {
public:
	A2D_Converter(const char * fileName, byte a2d_address) {	// A2D Converter Constructor
		fileName_ = fileName;
		a2d_address_ = a2d_address;
		fileDescr_ = 0;
	}

	void Initialize() {
		if ((fileDescr_ = open(fileName_, O_RDWR)) < 0) {		// Open port for reading and writing
			printf("Failed to open i2c port\n");
			exit(1);
		}

		// Set the port options and set the address of the device we wish to speak to:
		if (ioctl(fileDescr_, I2C_SLAVE, a2d_address_) < 0) {
			printf("Unable to get bus access to talk to slave\n");
			exit(1);
		}

	}

	void Read() {
		buf_[0] = 0x44; // Set A/D to auto increment mode + analog output enable flag (see p. 6 of PCF8591 datasheet)
		if ((write(fileDescr_, buf_, 1)) != 1) {		// Send control byte
				printf("Error writing to i2c slave\n");
				exit(1);
		}

		if ((read(fileDescr_, buf_, 5)) != 5) {		// Read 5 bytes from A/D first byte is garbage
			printf("Error reading from i2c slave\n");
			exit(1);
		}
	}

	byte Get(int channel) {							// Get the converted value stored in buf_[channel]
		return buf_[channel+1]; // First channel has garbage
	}

private:
	const char * fileName_;
	int fileDescr_;         // File description
	byte a2d_address_;      // I2C Address of PF8591 Chip
	byte buf_[4];  			// Buffer for data being read/ written on the i2c bus (4 bytes)
};


class Gpio_Expander{
protected:
	int fileDescr_;							// File description
	const char *fileName_;	// Name of the port we will be using (1 for Rev. 2, 0-Rev.1)
	byte  mcp_address_;      		// I2C Address of MCP23017 Chip
	unsigned char buf_[10];					// Buffer for data being read/ written on the i2c bus

	byte IODIRA_;
	byte IODIRB_;
	byte  GPIOA_;						// Register Address of Port A
	byte  GPIOB_;						// Register Address of Port B

	void Set_Register(byte reg, byte value){
		buf_[0] = reg;
		buf_[1] = value; // Set GPIOB0-7 high or low

		if ((write(fileDescr_, buf_, 2)) != 2) {		// Send register we want to read from (2 bytes)
			printf("Error writing to i2c slave\n");
			exit(1);
		}
	}

	byte Get_Register(byte reg){
		buf_[0] = reg;

		if ((write(fileDescr_, buf_, 1)) != 1) {		// Send register we want to read from (1 byte)
			printf("Error writing to i2c slave\n");
			exit(1);
		}

		if ((read(fileDescr_, buf_, 1)) != 1) {		// Read  (1 byte)
			printf("Error writing to i2c slave\n");
			exit(1);
		}

		return buf_[0];
	}

public:

	Gpio_Expander(const char *fileName, byte mcp_address) {
		fileName_ = fileName;
		mcp_address_ = mcp_address;
		fileDescr_ = 0;
		IODIRA_= 0x00;
		IODIRB_= 0x01;
		GPIOA_ = 0x12;
		GPIOB_ = 0x13;
	}

	void Initialize(){
		if ((fileDescr_ = open(fileName_, O_RDWR)) < 0) {		// Open port for reading and writing
			printf("Failed to open i2c port\n");
			exit(1);
		}
		// Set the port options and set the address of the device we wish to speak to:
		if (ioctl(fileDescr_, I2C_SLAVE, mcp_address_) < 0) {
			printf("Unable to get bus access to talk to slave\n");
			exit(1);
		}

	}

	void Configure_PortA(byte value){
		Set_Register(IODIRA_, value);
	}

	void Configure_PortB(byte value){
		Set_Register(IODIRB_, value);
	}

	void Set_PortA(byte value){
		Set_Register(GPIOA_, value);
	}

	void Set_PortB(byte value){
		Set_Register(GPIOB_, value);
	}

	byte Get_PortA(){
		return Get_Register(GPIOA_);
	}

	byte Get_PortB(){
		return Get_Register(GPIOB_);
	}
};


class Gpio_Buttons: public Gpio_Expander {
private:
    byte state_[16];
    byte debouncing_[16];
public:
    Gpio_Buttons(const char *fileName, byte mcp_address):
        Gpio_Expander(fileName, mcp_address){
        Configure_PortA(0xFF);  //Configure port A pins as inputs
        memset(state_, 0, 16);
        memset(debouncing_, 0, 16);
    }

    void Update(){
        byte readings = Get_PortA();

        for(int b = 0; b < 8; ++b){
            debouncing_[b] <<= 1;
            debouncing_[b] |= (readings & 0x01);
            readings >>= 1;
        }


        for(int b = 0; b < 16; ++b){
            if(debouncing_[b] == 0xFF){
                state_[b] = 1;
            }
            else if(debouncing_[b] == 0x00){
                state_[b] = 0;
            }
        }
    }

    byte getButtonState(int button){
        return state_[button];
    }
};

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
	struct timespec tim, tim2;				// Nanosleep function setup (0 seconds and 10ms)
	tim.tv_sec = 0;
	tim.tv_nsec = 10000000L;
	string filename = "/dev/i2c-1";
	const int MUX_CHANNELS = 8;
	byte board[8][8];
	Board b;
	movement m;
	PiTFTButton whiteButton(23);
	PiTFTButton blackButton(18);

	A2D_Converter a2d_1(filename.c_str(), 0x48);	// A2D address for both chips
	a2d_1.Initialize();
	A2D_Converter a2d_2(filename.c_str(), 0x49);
	a2d_2.Initialize();

	Gpio_Expander gpio1(filename.c_str(), 0x20);	//To instantiate a GPIO object (first GPIO chip)
	gpio1.Initialize();
	gpio1.Configure_PortB(0x00);	//Configure port B pins as outputs

	whiteButton.ConfigAsInput();
	blackButton.ConfigAsInput();

    while(true){
        if(nanosleep(&tim , &tim2) < 0 ){
            printf("Nano sleep system call failed \n");
        }
        if(blackButton.Pushed()){
            for(int mux_channel = 0; mux_channel < MUX_CHANNELS; mux_channel++){
                gpio1.Set_PortB(1<<mux_channel);
                a2d_1.Read();
                a2d_2.Read();
                board[mux_channel][0] = a2d_1.Get(0) < 0x25 ? 1 : 0;
                board[mux_channel][1] = a2d_1.Get(1) < 0x25 ? 1 : 0;
                board[mux_channel][2] = a2d_1.Get(2) < 0x25 ? 1 : 0;
                board[mux_channel][3] = a2d_1.Get(3) < 0x25 ? 1 : 0;
                board[mux_channel][4] = a2d_2.Get(0) < 0x25 ? 1 : 0;
                board[mux_channel][5] = a2d_2.Get(1) < 0x25 ? 1 : 0;
                board[mux_channel][6] = a2d_2.Get(2) < 0x25 ? 1 : 0;
                board[mux_channel][7] = a2d_2.Get(3) < 0x25 ? 1 : 0;
            }

            m = b.findMovement(board);
            /*printf("%c (%d, %d) (%d, %d)\n", m.piece, m.origin_row,
                   m.origin_column, m.target_row, m.target_column);*/
            if(m.origin_row != -1 && m.origin_column != -1 &&
               m.target_row != -1 && m.target_column != -1){
                b.move(m);
            }
            b.printBoard();
            PrintShadowBoard(&(board[0][0]));
        }
    }
}

int main(int argc, char **argv){
	ChessPi();
	return 0;
}
