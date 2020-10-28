/* 
 refer : https://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c/26423946
 for escape sequance usage. 
*/
#include <chrono>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <vector>

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

#define CHARS_PER_WORD		5
// #define RANDOM_INPUT
#define RAND_TEXT_SIZE		(CHARS_PER_WORD * 10)
#define CHAR_SET_SIZE		26 /* english alphabets */
#define WORD_PER_LINE		12
#define INPUT_FILE			"input1.txt"

using namespace std;
using namespace std::chrono;

vector<char> text;
vector<char> input;
struct termios orig_termios;

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() 
{
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(IXON);
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void readtext(const char *FileName, vector<char> &text)
{
	FILE *fptr = NULL;
	int iRetVal = 0;
	char ch = 0;
	if(FileName == NULL)
	{
		printf("Invalid Pointer\n");
	}
	
	fptr = fopen(FileName, "r");
	if(fptr != NULL)
	{
		while(1)
		{
			iRetVal = fread(&ch, sizeof(char), 1, fptr);
			if(feof(fptr))
			{
				break;
			}

			text.push_back(ch);
		}
		// printf("%d characters read from %s Success\n", text.size(), FileName);

		fclose(fptr);
	}
	else
	{
		printf("fopen failed..!\n");
	}
}

void print(vector<char> text)
{
	for(auto ch: text)
	{
		cout << ch;
	}
}

void randtext(vector<char>& text, int size)
{
	char ch = 0;
	srand(time(NULL));
	for(int i = 1; i <= size; i++)
	{
		if((i % (CHARS_PER_WORD * WORD_PER_LINE)) == 0)
		{
			ch = '\n';	
		}
		else if((i % CHARS_PER_WORD) == 0)
		{
			ch = ' ';
		}
		else
		{
			ch = (rand() % CHAR_SET_SIZE) + 'a';
			// ch = 'z' - (rand() % CHAR_SET_SIZE);
		}
		text.push_back(ch);
	}
	/* remove the trialing space */
	text.pop_back();
}

int main(int argc, char const *argv[])
{
	char ch = 0;
	int index = 0;
	int iRetVal = 0;
	int errors = 0;
	double words  = 0;
	double speed_wpm = 0;
	double accuracy = 0;

	/* added for adjusting position in output screen */
	int xPos = 0;

	#ifdef RANDOM_INPUT
		randtext(input, RAND_TEXT_SIZE);
	#else
		/* get the file name form the user */
		if(argc < 2)
		{
			printf("usage: %s [filename]\n", argv[0]);
			return 0;
		}
		else
		{
			// readtext(INPUT_FILE, input);	
			readtext(argv[1], input);
		}
		
	#endif
	cout << "Typing speed calculator\n";
	cout << "\n";
	print(input);
	cout << "\n\n";

	text.clear();
	enableRawMode();
	auto start = high_resolution_clock::now();
		
	while(text.size() < input.size())
	{
		ch = getchar();
		cout << ch;
		if(ch != input[index])
		{
			/* on receiving a invalid new line go up
				one line and go right xPos */
			if(ch == '\n')
			{
				/* go up one line */
				cout << "\033[1A";
				/* go right xPos */
				cout << "\033[" << xPos << "C";
			}
			else
			{
				cout << "\b";
			}
			errors++;
		}
		else
		{
			text.push_back(ch);
			index++;
			xPos++;

			/* reset the x position on every valid newline */
			if(ch == '\n')	
			{
				xPos = 0;
			}
		}

	}
	
	auto stop = high_resolution_clock::now();
	auto time = duration_cast<milliseconds>(stop - start);

	words = ((double)text.size() / (double)CHARS_PER_WORD);
	speed_wpm = (words / (time.count() / 1000)) * 60;
	accuracy = ((double)(text.size() - errors) / text.size()) * 100;
	cout << "\nwords typed: "  << words << " time: " << (time.count() / 1000) << " sec" << endl;
	cout << "Speed: " << speed_wpm << " wpm " << "Accuracy: " << accuracy << " %" << endl;

	return 0;
}
