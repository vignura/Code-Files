#include "../include/main.h"

/* global variables */
global_struct g_srt;

int main(int argc, char const *argv[])
{
	char ch = 0;
	int index = 0;
	int errors = 0;
	double words  = 0;
	double speed_wpm = 0;
	double accuracy = 0;

	/* added for adjusting position in output screen */
	int xPos = 0;

	#ifdef RANDOM_INPUT
		randtext(g_srt.input, RAND_TEXT_SIZE);
	#else
		/* get the file name form the user */
		if(argc < 2)
		{
			printf("usage: %s [filename]\n", argv[0]);
			return 0;
		}
		else
		{
			// readtext(INPUT_FILE, g_srt.input);	
			readtext(argv[1], g_srt.input);
		}
		
	#endif
	cout << "Typing Simulator\n";
	cout << "\n";
	print(g_srt.input);
	cout << "\n\n";

	g_srt.text.clear();
	enableRawMode();
	auto start = high_resolution_clock::now();
		
	while(g_srt.text.size() < g_srt.input.size())
	{
		ch = getchar();
		cout << ch;
		if(ch != g_srt.input[index])
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
			g_srt.text.push_back(ch);
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

	words = ((double)g_srt.text.size() / (double)CHARS_PER_WORD);
	speed_wpm = (words / (time.count() / 1000)) * 60;
	accuracy = ((double)(g_srt.text.size() - errors) / g_srt.text.size()) * 100;
	cout << "\nwords typed: "  << words << " time: " << (time.count() / 1000) << " sec" << endl;
	cout << "Speed: " << speed_wpm << " wpm " << "Accuracy: " << accuracy << " %" << endl;

	return 0;
}
