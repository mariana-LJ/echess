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
	A2D_Converter(const char * fileName, byte a2d_address) {
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

		buf_[0] = 0x00; // Set A/D to read channel 0
		if ((write(fileDescr_, buf_, 1)) != 1) {		// Send control byte
				printf("Error writing to i2c slave\n");
				exit(1);
		}

		buf_[0] = 0x44; // Set A/D to auto increment mode
		if ((write(fileDescr_, buf_, 1)) != 1) {		// Send control byte
				printf("Error writing to i2c slave\n");
				exit(1);
		}

		if((read(fileDescr_, buf_, 1)) != 1){				// Read previously stored value (possibly garbage)
			printf("Error reading from i2c slave\n");
			exit(1);
		}
	}

	void Read() {
		if ((read(fileDescr_, buf_, 4)) != 4) {		// Read 4 bytes from A/D
			printf("Error reading from i2c slave\n");
			exit(1);
		}
	}

	byte Get(int channel) {
		return buf_[channel];
	}

private:
	const char * fileName_;
	int fileDescr_;         // File description
	byte a2d_address_;      // I2C Address of PF8591 Chip
	byte buf_[4];  // Buffer for data being read/ written on the i2c bus
};


int main(int argc, char **argv)
{
	int i = 0;								// Auxiliary
	int b = 0;
	struct timespec tim, tim2;				// Nanosleep function setup
	tim.tv_sec = 0;
	tim.tv_nsec = 500000000L;
	string filename = "/dev/i2c-1";

	A2D_Converter a2d_1(filename.c_str(), 0x48);
	A2D_Converter a2d_2(filename.c_str(), 0x49);
	a2d_1.Initialize();
	a2d_2.Initialize();

	for(i = 0; i<100; i++) {
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

	return 0;
}
