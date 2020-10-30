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
			ch = (rand() % CHAR_SET_SIZE) + 'a';
			// ch = 'z' - (rand() % CHAR_SET_SIZE);
		}
		text.push_back(ch);
	}
	/* remove the trialing space */
	text.pop_back();
}
