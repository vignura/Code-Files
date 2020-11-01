#ifndef _TYPING_SIMULATOR_MAIN_H_
#define _TYPING_SIMULATOR_MAIN_H_

/* c++ headers */
#include <chrono>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <vector>
#include <ctime>

/* linux headers */
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>

/* name spaces */
using namespace std;
using namespace std::chrono;

/* project headers */
#include "../include/terminal.h"
#include "../include/fileio.h"
#include "../include/errorlog.h"

#define TYPE_SIM_SUCCESS		0
#define TYPE_SIM_FAILURE		-1

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
	error_db edb;
}global_struct;

extern global_struct g_srt;

void typing_speed_test(vector<char>& input, vector<char>& text, test_stat *tst);
int process_cmdline_args(int argc, const char *argv[], vector<char>& input);

#endif /* _TYPING_SIMULATOR_MAIN_H_ */
