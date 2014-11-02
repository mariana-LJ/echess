/*
 * PiTFTButton.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Mariana Lopez
 */

#ifndef PITFTBUTTON_H_
#define PITFTBUTTON_H_

class PiTFTButton {

public:
    PiTFTButton(int pin);
    ~PiTFTButton();
    void ConfigAsInput();
    bool Pushed();

private:
    static int  mem_fd;
    static void *gpio_map;

    // I/O access
    static volatile unsigned *gpio;

    int pin_;
    unsigned char debounce_;
    bool status_;
    void SetupIO();
};



#endif /* PITFTBUTTON_H_ */
