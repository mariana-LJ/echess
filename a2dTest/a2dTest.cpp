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

typedef unsigned char byte;

int main(int argc, char **argv)
{

	int fileDescr;							// File description
	char *fileName = "/dev/i2c-1";			// Name of the port we will be using (1 for Rev. 2, 0-Rev.1)
	const byte  a2d_address=0x48;      		// I2C Address of PF8591 Chip
	unsigned char buf[10];					// Buffer for data being read/ written on the i2c bus
	int i = 0;								// Auxiliary
	int b = 0;
	struct timespec tim, tim2;				// Nanosleep function setup
	tim.tv_sec = 0;
	tim.tv_nsec = 500000000L;

	if ((fileDescr = open(fileName, O_RDWR)) < 0) {		// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}

	// Set the port options and set the address of the device we wish to speak to:
	if (ioctl(fileDescr, I2C_SLAVE, a2d_address) < 0) {
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}

	buf[0] = 0x00; // Set A/D to read channel 0
	if ((write(fileDescr, buf, 1)) != 1) {		// Send control byte
			printf("Error writing to i2c slave\n");
			exit(1);
	}

	buf[0] = 0x44; // Set A/D to auto increment mode
	if ((write(fileDescr, buf, 1)) != 1) {		// Send control byte
			printf("Error writing to i2c slave\n");
			exit(1);
	}

	if((read(fileDescr, buf, 1)) != 1){				// Read previously stored value (possibly garbage)
		printf("Error reading from i2c slave\n");
		exit(1);
	}

	for(i = 0; i<100; i++) {
		//system("clear");
		if ((read(fileDescr, buf, 4)) != 4) {		// Read 5 bytes from A/D
			printf("Error reading from i2c slave\n");
			exit(1);
		} else {
			for(b = 0; b<4; b++){
				printf("%x  ",buf[b]); // Print last byte (5th byte)
			}
			printf("\n");
		}

		if(nanosleep(&tim , &tim2) < 0 ){
			  printf("Nano sleep system call failed \n");
		}
	}

	return 0;
}
