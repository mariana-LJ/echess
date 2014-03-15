/*
 * i2cLed.c
 *
 *  Created on: Feb 22, 2014
 *      Author: mlj
 */


// CMPS03 example c code for the Raspberry pi
//
// Reads the bearing from the CMPS03 and displays
// it on the screen.
//
// By James Henderson, 2012


#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef unsigned char byte;

int main(int argc, char **argv)
{

	int fileDescr;							// File description
	char *fileName = "/dev/i2c-1";			// Name of the port we will be using (1 for Rev. 2, 0-Rev.1)
	const byte  a2d_address=0x48;      		// I2C Address of PF8591 Chip
	const byte  control_byte = 0x00;				// Register Address of channel control_byte (A/D channel 0)
	unsigned char buf[10];					// Buffer for data being read/ written on the i2c bus
	int i = 0;								// Auxiliary

	if ((fileDescr = open(fileName, O_RDWR)) < 0) {		// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}

	// Set the port options and set the address of the device we wish to speak to:
	if (ioctl(fileDescr, I2C_SLAVE, a2d_address) < 0) {
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}

	// This is the register we want to read from:
	buf[0] = control_byte; // Set A/D to read channel 0

	if ((write(fileDescr, buf, 1)) != 1) {		// Send register we want to read from (2 bytes)
		printf("Error writing to i2c slave\n");
		exit(1);
	}

	for(i = 0; i<30; i++) {
		if ((read(fileDescr, buf, 1)) != 1) {		// Send register we want to read from (2 bytes)
				printf("Error writing to i2c slave\n");
				exit(1);
		} else {
			printf("%u \n",buf[0]);
		}

		sleep(1);
	}

	return 0;
}
