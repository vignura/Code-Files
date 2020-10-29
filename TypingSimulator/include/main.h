#ifndef _TYPING_SIMULATOR_MAIN_H_
#define _TYPING_SIMULATOR_MAIN_H_

/* c++ headers */
#include <chrono>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <vector>

/* linux headers */
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

/* name spaces */
using namespace std;
using namespace std::chrono;

/* project headers */
#include "../include/terminal.h"
#include "../include/fileio.h"

#define CHARS_PER_WORD		5
// #define RANDOM_INPUT
#define RAND_TEXT_SIZE		(CHARS_PER_WORD * 10)
#define CHAR_SET_SIZE		26 /* english alphabets */
#define WORD_PER_LINE		12
#define INPUT_FILE			"input1.txt"

/* global struct */
typedef struct {

	vector<char> text;
	vector<char> input;
}global_struct;

extern global_struct g_srt;

#endif /* _TYPING_SIMULATOR_MAIN_H_ */