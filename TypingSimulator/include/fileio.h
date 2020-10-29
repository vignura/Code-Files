#ifndef _TYPING_SIMULATOR_FILEIO_H_
#define _TYPING_SIMULATOR_FILEIO_H_

void readtext(const char *FileName, vector<char> &text);
void print(vector<char> text);
void randtext(vector<char>& text, int size);

#endif /* _TYPING_SIMULATOR_FILEIO_H_ */