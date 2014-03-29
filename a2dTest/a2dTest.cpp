/*
 *  Created on: Mar 16, 2014
 *      Author: mlj
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


void Test_A2D()
{
	int i = 0;								// Auxiliary variables
	int b = 0;
	struct timespec tim, tim2;				// Nanosleep function setup (0 seconds and 500ms)
	tim.tv_sec = 0;
	tim.tv_nsec = 500000000L;
	string filename = "/dev/i2c-1";

	A2D_Converter a2d_1(filename.c_str(), 0x48);	// A2D address for both chips
	A2D_Converter a2d_2(filename.c_str(), 0x49);
	a2d_1.Initialize();
	a2d_2.Initialize();

	for(i = 0; i<100; i++) {// The result: 8 converted values in a row read 100 times and separated by a new line
		a2d_1.Read();
		a2d_2.Read();

		for(b = 0; b<4; b++){
			printf("%x ", a2d_1.Get(b));
		}
		for(b = 0; b<4; b++){
			printf("%x ", a2d_2.Get(b));
		}
		printf("\n");

		if(nanosleep(&tim , &tim2) < 0 ){
			  printf("Nano sleep system call failed \n");
		}
	}
}

class Gpio_Expander{
public:
	Gpio_Expander(const char *fileName, byte mcp_address) {
		GPIOA_ = 0x12;
		GPIOB_ = 0x13;

		fileName_ = fileName;
		mcp_address_ = mcp_address;
		fileDescr_ = 0;
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

	void Configure_Port_B(byte value){
		// This is the register we want to read from:
		buf_[0] = 0x01;
		buf_[1] = value; // Set GPIO0-7 to outputs

		if ((write(fileDescr_, buf_, 2)) != 2) {		// Send register we want to read from (2 bytes)
			printf("Error writing to i2c slave\n");
			exit(1);
		}
	}

	void Set_Port_B(byte value){
		buf_[0] = GPIOB_;
		buf_[1] = value; // Set GPIOB0-7 high or low

		if ((write(fileDescr_, buf_, 2)) != 2) {		// Send register we want to read from (2 bytes)
			printf("Error writing to i2c slave\n");
			exit(1);
		}
	}
private:
	int fileDescr_;							// File description
	const char *fileName_;	// Name of the port we will be using (1 for Rev. 2, 0-Rev.1)
	byte  mcp_address_;      		// I2C Address of MCP23017 Chip
	byte  GPIOA_;						// Register Address of Port A
	byte  GPIOB_;						// Register Address of Port B
	unsigned char buf_[10];					// Buffer for data being read/ written on the i2c bus

};

void Test_Gpio_Expander() {

	int i = 0;
	string filename = "/dev/i2c-1";
	struct timespec tim, tim2;				// Nanosleep function setup (1 second and 0ms)
	tim.tv_sec = 1;
	tim.tv_nsec = 0;

	Gpio_Expander gpio1(filename.c_str(), 0x20);	//To instantiate a GPIO object (first GPIO chip)
	gpio1.Initialize();
	gpio1.Configure_Port_B(0x00);	//Configure port B pins as outputs

	for(i = 0; i < 8; i++){ // Test three outputs from one GPIO (turn on and off 3 LEDs sequentially)
		gpio1.Set_Port_B(i);
		if(nanosleep(&tim , &tim2) < 0 ){
			printf("Nano sleep system call failed \n");
		}
	}
	gpio1.Set_Port_B(0x00);	// Set GPIOB0-7 low
	gpio1.Configure_Port_B(0xFF); // Leave GPIOB0-7 as inputs

}

void Test_MUX(){
	struct timespec tim, tim2;				// Nanosleep function setup (0 seconds and 10ms)
	tim.tv_sec = 0;
	tim.tv_nsec = 10000000L;
	string filename = "/dev/i2c-1";
	const int MUX_CHANNELS = 4;
	byte board[4][4];

	A2D_Converter a2d_1(filename.c_str(), 0x48);	// A2D address for both chips
	a2d_1.Initialize();
	A2D_Converter a2d_2(filename.c_str(), 0x49);
	a2d_2.Initialize();

	Gpio_Expander gpio1(filename.c_str(), 0x20);	//To instantiate a GPIO object (first GPIO chip)
	gpio1.Initialize();
	gpio1.Configure_Port_B(0x00);	//Configure port B pins as outputs

	for(int mux_channel = 0; mux_channel < MUX_CHANNELS; mux_channel++){
		gpio1.Set_Port_B(mux_channel);
		/*if(nanosleep(&tim , &tim2) < 0 ){
			printf("Nano sleep system call failed \n");
		}*/
		a2d_1.Read();
		a2d_2.Read();
		board[mux_channel][0] = a2d_1.Get(0);
		board[mux_channel][1] = a2d_1.Get(1);
		board[mux_channel][2] = a2d_2.Get(0);
		board[mux_channel][3] = a2d_2.Get(1);
	}

	system("clear");
	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			printf("%x\t", board[row][col]);
		}
		printf("\n");
	}
	printf("\n");

}

int main(int argc, char **argv){
	Test_MUX();
	return 0;
}
