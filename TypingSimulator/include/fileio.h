#ifndef _TYPING_SIMULATOR_FILEIO_H_
#define _TYPING_SIMULATOR_FILEIO_H_

/* refer https://stackoverflow.com/questions/13104478/uniformity-of-random-numbers-taken-modulo-n */
#define UNIFORMITY_FACTOR	1000

typedef struct{
	double words;
	double time;
	double speed;
	double accuracy;
}typing_stat;

void readtext(const char *FileName, vector<char> &text);
void print(vector<char> text);
void randtext(vector<char>& text, int size);
int problemtext(vector<char>& text, int char_count, int textsize);
void print_typing_stat(typing_stat* tst);

#endif /* _TYPING_SIMULATOR_FILEIO_H_ */
