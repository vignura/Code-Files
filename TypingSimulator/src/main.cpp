#include "../include/main.h"

/* global variables */
global_struct g_srt;

int main(int argc, char const *argv[])
{
	/* process command line inputs */
	if(process_cmdline_args(argc, argv, g_srt.input) == TYPE_SIM_SUCCESS)
	{
		/* run the test */
		typing_speed_test(g_srt.input, g_srt.text);	
	}

	return 0;
}


void typing_speed_test(vector<char>& input, vector<char>& text)
{
	char ch = 0;
	int index = 0;
	int errors = 0;
	double words  = 0;
	double speed_wpm = 0;
	double accuracy = 0;
	/* added for adjusting position in output screen */
	int xPos = 0;

	read_error_db(&g_srt.edb);
	cout << "Typing speed test\n";
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
				update_errors(&g_srt.edb, input[index]);
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

	write_error_db(&g_srt.edb);
	auto stop = high_resolution_clock::now();
	auto time = duration_cast<milliseconds>(stop - start);

	words = ((double)text.size() / (double)CHARS_PER_WORD);
	speed_wpm = (words / (time.count() / 1000)) * 60;
	accuracy = ((double)(text.size() - errors) / text.size()) * 100;
	cout << "\nwords typed: "  << words << " time: " << (time.count() / 1000) << " sec" << endl;
	cout << "Speed: " << speed_wpm << " wpm " << "Accuracy: " << accuracy << " %" << endl;
}

int process_cmdline_args(int argc, const char *argv[], vector<char>& input)
{
	int iret = 0;
	int words = 0;
	int chars = 0;
	char arg = 0;
	char filename[256] = {0};

	/* get the file name form the user */
	if(argc < 3)
	{
		printf("usage: %s [option] [parm]\n", argv[0]);
		return TYPE_SIM_FAILURE;
	}
	
	/* get the argument */
	sscanf(argv[1], "-%c", &arg);
	// printf("argument: %c\n", arg);

	switch(arg)
	{
		case 'r':
			/* read the word count from argv */
			iret = sscanf(argv[2], "%d", &words);
			if(iret == 1)
			{
				randtext(input, (CHARS_PER_WORD * words));
				iret = TYPE_SIM_SUCCESS;
			}
			else
			{
				iret = TYPE_SIM_FAILURE;
				printf("invalid word count\n");
			}
		break;

		case 'f':
			/* read the file name form the argv */
			iret = sscanf(argv[2], "%s", filename);
			if(iret == 1)
			{
				readtext(filename, input);
				iret = TYPE_SIM_SUCCESS;
			}
			else
			{
				iret = TYPE_SIM_FAILURE;
				printf("invalid filename\n");
			}
		break;

		case 'd':
			/* display error log and return failure as
			   we want the program to exit */
			display_errors_log();
			iret = TYPE_SIM_FAILURE;
		break;

		case 'p':
			/* generate random words with problem characters */
			iret = sscanf(argv[2], "%d", &chars);
			if(iret == 1)
			{
				if(problemtext(input, chars, (12 * CHARS_PER_WORD)) == TYPE_SIM_SUCCESS)
				{
					iret = TYPE_SIM_SUCCESS;	
				}
				else
				{
					iret = TYPE_SIM_FAILURE;
					printf("unable to generate problem text\n");	
				}
			}
			else
			{
				iret = TYPE_SIM_FAILURE;
				printf("invalid character count\n");
			}
		break;
		
		default:
			printf("invalid option\n");
			iret = TYPE_SIM_FAILURE;
	}

	return iret;
}
