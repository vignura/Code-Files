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

void print_test_stat(test_stat* tst)
{
	if(tst != NULL)
	{
		printf("words typed: %.01f time: %.02f sec\n", tst->words, tst->time);
		printf("speed: %.02f wpm accuracy: %.02f %%\n", tst->speed, tst->accuracy);
	}
}

int read_typing_stat(vector<typing_stat>& vtstat, unsigned int stat_count)
{
	int ret = 0;
	FILE *fp = NULL;
	long filesize = 0;
	typing_stat tstat = {0};
	typing_stat_header tstat_header = {0};

	fp = fopen(TYPING_STAT_FILE, "rb");
	if(fp == NULL)
	{
		printf("unable to open %s\n", TYPING_STAT_FILE);
		return TYPE_SIM_FAILURE;
	}

	/* get the file size */
	filesize = get_filesize(fp->_fileno);

	/* read the file header */
	if(fread(&tstat_header, sizeof(tstat_header), 1, fp) != 1)
	{
		printf("unable to read %s\n", ERROR_DB_FILE_NAME);
		return TYPE_SIM_FAILURE;
	}
	else
	{
		printf("stat count: %ld\n", tstat_header.stat_count);
	}
	
	/* read the stat records from the file in reverse order */
	for(unsigned int i = 0; ((i < tstat_header.stat_count) && (i < stat_count)); i++)
	{
		if(fseek(fp, (filesize - ((i +1) * sizeof(typing_stat))), SEEK_SET) != 0)
		{
			perror("unable to seek form the end of the file");
			return TYPE_SIM_FAILURE;
		}

		/* read the file header */
		ret = fread(&tstat, sizeof(typing_stat), 1, fp);
		if(ret != 1)
		{
			printf("ret: %d\n", ret);
			perror("unable to read stats");
			return TYPE_SIM_FAILURE;
		}		

		vtstat.push_back(tstat);
	}

	fclose(fp);

	return TYPE_SIM_SUCCESS;
}

int append_typing_stat(typing_stat* tstat)
{
	FILE *fp = NULL;
	typing_stat_header tstat_header = {0};

	fp = fopen(TYPING_STAT_FILE, "rb");
	if(fp == NULL)
	{
		printf("unable to open %s\n", TYPING_STAT_FILE);
		printf("creating %s\n", TYPING_STAT_FILE);

		/* create a new file as it does not exist */
		fp = fopen(TYPING_STAT_FILE, "wb");
		if(fp == NULL)
		{
			printf("unable to create %s\n", TYPING_STAT_FILE);
			return TYPE_SIM_FAILURE;
		}	

		/* write the empty header */
		if(fwrite(&tstat_header, sizeof(typing_stat_header), 1, fp) != 1)
		{
			printf("unable to write header to %s\n", ERROR_DB_FILE_NAME);
			return TYPE_SIM_FAILURE;
		}

		/* close the file */
		fclose(fp);
	}
	else{

		/* read the file header */
		if(fread(&tstat_header, sizeof(typing_stat_header), 1, fp) != 1)
		{
			printf("unable to read %s\n", ERROR_DB_FILE_NAME);
			return TYPE_SIM_FAILURE;
		}
		
		/* close the file */
		fclose(fp);
	}

	/* append the stat record to the end of the file */
	fp = fopen(TYPING_STAT_FILE, "ab");
	if(fp == NULL)
	{
		printf("unable to open %s\n", TYPING_STAT_FILE);
		return TYPE_SIM_FAILURE;
	}

	if(fwrite(tstat, sizeof(typing_stat), 1, fp) != 1)
	{
		printf("unable to append stat to %s\n", ERROR_DB_FILE_NAME);
		return TYPE_SIM_FAILURE;
	}

	fclose(fp);

	/* update the header */
	fp = fopen(TYPING_STAT_FILE, "r+b");
	if(fp == NULL)
	{
		printf("unable to open %s\n", TYPING_STAT_FILE);
		return TYPE_SIM_FAILURE;
	}

	/* update the header */
	tstat_header.stat_count++;
	if(fwrite(&tstat_header, sizeof(tstat_header), 1, fp) != 1)
	{
		printf("unable to update header to %s\n", ERROR_DB_FILE_NAME);
		return TYPE_SIM_FAILURE;
	}

	fclose(fp);

	return TYPE_SIM_SUCCESS;
}

void display_typing_stat(int stat_count)
{
	vector<typing_stat> vtstat;
	char *date_time = NULL;

	if(read_typing_stat(vtstat, stat_count) == TYPE_SIM_SUCCESS)
	{
		printf("TYPING STATS:\n");

		for(unsigned int i = 0; i < vtstat.size(); i++)
		{
			date_time = ctime(&vtstat[i].test_time);
			printf("%s", date_time);
			print_test_stat(&vtstat[i].tstat);
			printf("\n");
		}
	}
	else
	{
		printf("unable to display typing stats\n");
	}
}

long get_filesize(int fd)
{
    struct stat stat_buf = {0};
    int ret =  0;
    
    ret = fstat(fd, &stat_buf);
    if(ret != 0)
    {
    	perror("unable to read file size");
    	return TYPE_SIM_FAILURE;
    }

    return stat_buf.st_size;
}


int mistyped_words(vector<char>& text, unsigned int word_count)
{
	int index = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	vector<string> mistyped_words;

	/* read mistyped words from file */
	if(read_mistyped_words(mistyped_words) != TYPE_SIM_SUCCESS)
	{
		printf("unable to read mistyped words\n");
		return TYPE_SIM_FAILURE;
	}

	// print_words(mistyped_words);

	/* get some random words form mistyped words */
	srand(time(NULL));

	for(i = 1; i <= word_count; i++)
	{
		index = (rand() / UNIFORMITY_FACTOR) % mistyped_words.size();
		
		for(j = 0; j < mistyped_words[index].size(); j++)
		{
			text.push_back(mistyped_words[index][j]);	
		}

		if(i % WORD_PER_LINE == 0)
		{
			text.push_back('\n');
		}
		else
		{
			text.push_back(' ');		
		}
	}
	/* remove the trailing space */
	text.pop_back();

	return TYPE_SIM_SUCCESS;
}