#include "../include/main.h"

/* global variables */
global_struct g_srt;

int main(int argc, char const *argv[])
{
	typing_stat tystat = {0};
	vector<string> mistyped_words;

	/* process command line inputs */
	if(process_cmdline_args(argc, argv, g_srt.input) == TYPE_SIM_SUCCESS)
	{
		/* run the test */
		typing_speed_test(g_srt.input, g_srt.text, &tystat.tstat);
		// printf("\n\n");
		// print(g_srt.text);
		printf("\n\n");
		print_test_stat(&tystat.tstat);

		/* update the typing stat database */	
		tystat.test_time = time(NULL);
		append_typing_stat(&tystat);

		/* find mistyped words */
		find_mistyped_words(g_srt.input, g_srt.text, mistyped_words);
		if(mistyped_words.size() > 0)
		{
			write_mistyped_words(mistyped_words);
			// printf("\nmistyped words:\n");
			// print_words(mistyped_words);
		}
	}

	return 0;
}

void typing_speed_test(vector<char>& input, vector<char>& text, test_stat *tst)
{
	char ch = 0;
	unsigned int index = 0;
	int errors = 0;
	
	read_error_db(&g_srt.edb);
	cout << "Typing speed test\n\n";
	print(input);
	cout << "\n\n";

	text.clear();
	enableRawMode();

	auto start = high_resolution_clock::now();
		
	while(index < input.size())
	{
		ch = getchar();
		if(ch != input[index])
		{
			update_errors(&g_srt.edb, input[index]);
			errors++;
		}
		else
		{
			cout << ch;
			index++;
		}

		text.push_back(ch);
	}

	write_error_db(&g_srt.edb);

	auto stop = high_resolution_clock::now();
	auto time = duration_cast<milliseconds>(stop - start);

	tst->time =  (time.count() / 1000.00);
	tst->words = ((double)input.size() / (double)CHARS_PER_WORD);
	tst->speed = (tst->words / tst->time) * 60;
	tst->accuracy = ((double)(input.size() - errors) / input.size()) * 100;
}

int process_cmdline_args(int argc, const char *argv[], vector<char>& input)
{
	int iret = 0;
	int words = 0;
	int chars = 0;
	int stat_count = 0;
	char arg = 0;
	char filename[256] = {0};
	char option[128] = {0};

	/* get the file name form the user */
	if(argc < 2)
	{
		printf("usage: %s [option] [parm]\n", argv[0]);
		return TYPE_SIM_FAILURE;
	}
	
	/* get the argument */
	sscanf(argv[1], "-%c", &arg);
	// printf("argument: %c\n", arg);

	switch(arg)
	{
		case '-':
			sscanf(argv[1], "--%s", option);
			if(strncmp(option, "help", sizeof(option)) == 0)
			{
				printf("Typing simulator\n"
					    "Test your typing speed, find your problem charcters and get better with typing simulator.\n"
					    "Options:\n"
					    "\t-r\tgenerate n number of random words\n"
					    "\t-f\tuse file as input for typing test\n"
					    "\t-d\tdisplay stats [E - error stats; T - last n typing stats]\n"
					    "\t-p\tgenerate n random words using the top n number of problem charcters\n"
					    "\t-m\tuse n random mistyped words\n");
			}
			else
			{
				printf("invalid option\n");
			}

			iret = TYPE_SIM_FAILURE;	
		break;

		case 'r':
			if(argc < 3)
			{
				printf("usage: %s [option] [parm]\n", argv[0]);
				iret = TYPE_SIM_FAILURE;
			}
			else{
				/* read the word count from argv */
				if(sscanf(argv[2], "%d", &words) == 1)
				{
					randtext(input, (CHARS_PER_WORD * words));
					iret = TYPE_SIM_SUCCESS;
				}
				else
				{
					iret = TYPE_SIM_FAILURE;
					printf("invalid word count\n");
				}
			}
		break;

		case 'f':
			if(argc < 3)
			{
				printf("usage: %s [option] [parm]\n", argv[0]);
				iret = TYPE_SIM_FAILURE;
			}
			else{
				/* read the file name form the argv */
				if(sscanf(argv[2], "%s", filename) == 1)
				{
					readtext(filename, input);
					iret = TYPE_SIM_SUCCESS;
				}
				else
				{
					iret = TYPE_SIM_FAILURE;
					printf("invalid filename\n");
				}
			}
		break;

		case 'd':
			if(argc < 3)
			{
				printf("usage: %s [option] [parm]\n", argv[0]);
			}
			else{
				/* read the stat type argv */
				if(sscanf(argv[2], "%c", &arg) == 1)
				{
					switch(arg)
					{
						case 'E':
							/* display error log and return failure as
				   			we want the program to exit */
							display_errors_log();
						break;

						case 'T':
							if(argc < 4)
							{
								printf("enter stat count\n");
							}
							else
							{	
								if(sscanf(argv[3], "%d", &stat_count) == 1)
								{				
									display_typing_stat(stat_count);	
								}
								else
								{
									printf("invalid stat count\n");		
								}
							}
							
						break;

						default:
						;
					}
					iret = TYPE_SIM_SUCCESS;
				}
				else
				{
					printf("invalid stat option\n");
				}
			}
			iret = TYPE_SIM_FAILURE;
		break;

		case 'p':
			if(argc < 4)
			{
				printf("usage: %s [option] [parm]\n", argv[0]);
				iret = TYPE_SIM_FAILURE;
			}
			else{
				/* generate random words with problem characters */
				if(sscanf(argv[2], "%d", &chars) == 1)
				{
					if(sscanf(argv[3], "%d", &words) == 1)
					{
						if(problemtext(input, chars, (words * CHARS_PER_WORD)) == TYPE_SIM_SUCCESS)
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
						printf("invalid word count\n");		
					}
				}
				else
				{
					iret = TYPE_SIM_FAILURE;
					printf("invalid character count\n");
				}
			}
		break;

		case 'm':
			if(argc < 3)
			{
				printf("usage: %s [option] [parm]\n", argv[0]);
				iret = TYPE_SIM_FAILURE;
			}
			else{
				/* read the word count from argv */
				if(sscanf(argv[2], "%d", &words) == 1)
				{
					if(mistyped_words(input, words) == TYPE_SIM_SUCCESS)
					{
						iret = TYPE_SIM_SUCCESS;
					}
					else
					{
						iret = TYPE_SIM_FAILURE;
					}
				}
				else
				{
					iret = TYPE_SIM_FAILURE;
					printf("invalid word count\n");
				}
			}
		break;
		
		default:
			printf("invalid option\n");
			iret = TYPE_SIM_FAILURE;
	}

	return iret;
}
