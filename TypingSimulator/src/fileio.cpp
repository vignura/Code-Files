#include "../include/main.h"

void readtext(const char *FileName, vector<char> &text)
{
	char ch = 0;
	int iret = 0;
	FILE *fptr = NULL;

	if(FileName == NULL)
	{
		printf("Invalid Pointer\n");
	}
	
	fptr = fopen(FileName, "r");
	if(fptr != NULL)
	{
		while(1)
		{
			if(feof(fptr))
			{
				break;
			}

			iret = fread(&ch, sizeof(char), 1, fptr);
			if(iret == 1)
			{
				text.push_back(ch);
			}
			else
			{
				break;
			}
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
			/* uniformity factor is added as lower bits of rand output
			 are not distributed uniformaly, so dividing by UNIFORMITY_FACTOR 
			 */
			ch = ((rand() / UNIFORMITY_FACTOR) % CHAR_SET_SIZE) + 'a';
			// ch = 'z' - (rand() % CHAR_SET_SIZE);
		}
		text.push_back(ch);
	}
	/* remove the trialing space */
	text.pop_back();
}

int problemtext(vector<char>& text, int char_count, int textsize)
{
	int ret = 0;
	error_db edb = {0};
	error_stat est = {0};
	char ch = 0;

	/* read error database */
	if(read_error_db(&edb) != TYPE_SIM_SUCCESS)
	{
		return TYPE_SIM_FAILURE;
	}

	/* compute error stats */
	compute_error_stats(&edb, &est);

	/* generate random text for top
	   problem characters (ie high error count) */
	srand(time(NULL));
	for(int i = 1; i <= textsize; i++)
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
			/* uniformity factor is added as lower bits of rand output
			 are not distributed uniformaly, so dividing by UNIFORMITY_FACTOR 
			 */
			ch = est.charset[((rand() / UNIFORMITY_FACTOR) % char_count)];
		}
		text.push_back(ch);
	}

	/* remove the trialing space */
	text.pop_back();

	return ret;
}
