/*
 * common.h
 *
 *  Created on: Jun 19, 2014
 *      Author: acp
 */

#ifndef COMMON_H_
#define COMMON_H_

struct square{
  int row; // ranks: 1-8 -> representation: 0-7
  int column; // files: a=0, b=1,... h=7
  char piece; // the possible piece occupying a square
};



#endif /* COMMON_H_ */
