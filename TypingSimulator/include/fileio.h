#ifndef _TYPING_SIMULATOR_FILEIO_H_
#define _TYPING_SIMULATOR_FILEIO_H_

/* refer https://stackoverflow.com/questions/13104478/uniformity-of-random-numbers-taken-modulo-n */
#define UNIFORMITY_FACTOR	1000

void readtext(const char *FileName, vector<char> &text);
void print(vector<char> text);
void randtext(vector<char>& text, int size);
int problemtext(vector<char>& text, int char_count, int textsize);

#endif /* _TYPING_SIMULATOR_FILEIO_H_ */
