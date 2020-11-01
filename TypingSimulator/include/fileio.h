#ifndef _TYPING_SIMULATOR_FILEIO_H_
#define _TYPING_SIMULATOR_FILEIO_H_

/* refer https://stackoverflow.com/questions/13104478/uniformity-of-random-numbers-taken-modulo-n */
#define UNIFORMITY_FACTOR	1000
#define TYPING_STAT_FILE	"typing_stat.bin"

#pragma pack(push, 1)

typedef struct{
	double words;
	double time;
	double speed;
	double accuracy;
}test_stat;

typedef struct{
	test_stat tstat;
	time_t test_time;
}typing_stat;

typedef struct{
	unsigned long stat_count;
}typing_stat_header;

#pragma pack(pop)

void readtext(const char *FileName, vector<char> &text);
void print(vector<char> text);
void randtext(vector<char>& text, int size);
int problemtext(vector<char>& text, int char_count, int textsize);
void print_test_stat(test_stat* tst);
int read_typing_stat(vector<typing_stat>& vtstat, unsigned int stat_count);
int append_typing_stat(typing_stat* tstat);
void display_typing_stat(int stat_count);
long get_filesize(int fd);

#endif /* _TYPING_SIMULATOR_FILEIO_H_ */
