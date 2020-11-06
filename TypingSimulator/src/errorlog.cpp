#include "../include/main.h"

int read_error_db(error_db* edb)
{
	int ret = 0;
	FILE *fp = NULL;

	fp = fopen(ERROR_DB_FILE_NAME, "rb");
	if(fp == NULL)
	{
		printf("unable to open %s\n", ERROR_DB_FILE_NAME);
		return TYPE_SIM_FAILURE;
	}

	ret = fread(edb, sizeof(error_db), 1, fp);
	if(ret != 1)
	{
		printf("unable to read %s\n", ERROR_DB_FILE_NAME);
		return TYPE_SIM_FAILURE;
	}

	fclose(fp);

	return TYPE_SIM_SUCCESS;
}

int write_error_db(error_db* edb)
{
	int ret = 0;
	FILE *fp = NULL;

	fp = fopen(ERROR_DB_FILE_NAME, "wb");
	if(fp == NULL)
	{
		printf("unable to open %s\n", ERROR_DB_FILE_NAME);
		return TYPE_SIM_FAILURE;
	}

	ret = fwrite(edb, sizeof(error_db), 1, fp);
	if(ret != 1)
	{
		printf("unable to write %s\n", ERROR_DB_FILE_NAME);
		return TYPE_SIM_FAILURE;
	}

	fclose(fp);

	return TYPE_SIM_SUCCESS;
}

void update_errors(error_db* edb, char error)
{
	int index = 0;
	/* convert to lower case */
	error = tolower(error);

	/* only log alphabets */
	if((error >= 'a') && (error <= 'z'))
	{
		index =  error - 'a';
		edb->error_count[index]++;
		edb->total_errors++;
	}
}

void display_errors_log()
{
	int index = 0;
	error_db edb = {0};
	error_stat est = {0};

	printf("ERROR STATS\n");

	/* read error db */
	if(read_error_db(&edb) == TYPE_SIM_SUCCESS)
	{
		compute_error_stats(&edb, &est);

		for(index = 0; index < ERROR_CHAR_SET_SIZE; index++)
		{
			printf("%c: %ld (%.02f)\n", est.charset[index], est.edb.error_count[index],
				  (((double)est.edb.error_count[index] / (double)est.edb.total_errors) * 100));
		}

		printf("total errors: %lld\n", est.edb.total_errors);
	}
	else
	{
		printf("unable to display error log\n");
	}
}

void compute_error_stats(error_db* edb, error_stat* est)
{
	/* copy the error data base */
	memcpy(&est->edb, edb, sizeof(error_db));

	/* intialse the charset with alphabets */
	for(int i = 0; i < ERROR_CHAR_SET_SIZE; i++)
	{
		est->charset[i] = ('a' + i);
	}

	/* sort descending */
	for(int i = 0; i < ERROR_CHAR_SET_SIZE; i++)
	{	
		for(int j = (i +1); j < ERROR_CHAR_SET_SIZE; j++)
		{
			if(est->edb.error_count[i] < est->edb.error_count[j])
			{
				swap_char(&est->charset[i], &est->charset[j]);
				swap_long(&est->edb.error_count[i], &est->edb.error_count[j]);
			}
		}
	}
}

void swap_char(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_long(unsigned long *a, unsigned long *b)
{
	unsigned long tmp = *a;
	*a = *b;
	*b = tmp;
}

void find_mistyped_words(vector<char>& input, vector<char>& text, vector<string>& mistyped_words)
{
	unsigned int i = 0;
	unsigned int j = 0;
	int ret = 0;

	vector<string> input_words;
	vector<string> text_words;
	
	/* tokenize the strings */
	string_split(input, ' ', input_words);
	string_split(text, ' ', text_words);
	// printf("words in input\n");
	// print_words(input_words);

	for(i = 0, j = 0; (i < input_words.size()) && (j < text_words.size()); i++, j++)
	{
		ret = input_words[i].compare(text_words[j]); 
		// printf("comparing %s and %s: %d\n", input_words[i].c_str(), text_words[j].c_str(), ret);
		if(ret != 0)
		{
			// printf("input size: %ld text size: %ld\n", input_words[i].size(), text_words[j].size());
			/* if the size of input word is greater than text word, then
			 user has pressed space before completing the current word hence 
			 skip next word */
			if(input_words[i].size() > text_words[j].size())
			{
				j++;
			}
			mistyped_words.push_back(input_words[i]);
		}
	}
}

void string_split(vector<char>& str, char c, vector<string>& words)
{
	unsigned int index = 0;
	string word;

	for(index = 0; index < str.size(); index++)
	{
		if(str[index] == c)
		{
			words.push_back(word);
			word.clear();
		}
		else
		{
			word.push_back(str[index]);
		}
	}

	/* push back the last word */
	words.push_back(word);
}

void print_words(vector<string>& words)
{
	unsigned int i = 0;

	for(i = 0; i < words.size(); i++)
	{
		printf("%s\n", words[i].c_str());
	}
}

int read_mistyped_words(vector<string>& words)
{
	FILE *fp = NULL;
	char str[256] = {0};
	string word;

	fp = fopen(MISTYPED_WORDS_FILE_NAME, "r");
	if(fp == NULL)
	{
		printf("unable to open %s\n", MISTYPED_WORDS_FILE_NAME);
		return TYPE_SIM_FAILURE;
	}

	while(fscanf(fp, "%s", str) != EOF)
	{
		// printf("read: %s\n", str);	
		word = str;
		words.push_back(word);
	}

	fclose(fp);

	// print_words(words);

	return TYPE_SIM_SUCCESS;
}

int write_mistyped_words(vector<string>& words)
{
	FILE *fp = NULL;
	unsigned int i = 0;
	vector<string> mistyped_words;

	if(read_mistyped_words(mistyped_words) != TYPE_SIM_SUCCESS)
	{
		printf("unable to open %s\n", MISTYPED_WORDS_FILE_NAME);
		printf("creating %s\n", MISTYPED_WORDS_FILE_NAME);

		/* create the file */
		fp = fopen(MISTYPED_WORDS_FILE_NAME, "w");
		if(fp == NULL)
		{
			printf("unable to create %s\n", MISTYPED_WORDS_FILE_NAME);
			return TYPE_SIM_FAILURE;			
		}
	}
	else
	{
		/* create the file */
		fp = fopen(MISTYPED_WORDS_FILE_NAME, "a");
		if(fp == NULL)
		{
			printf("unable to open %s\n", MISTYPED_WORDS_FILE_NAME);
			return TYPE_SIM_FAILURE;			
		}	
	}

	for(i = 0; i < words.size(); i++)
	{
		if(find_string(mistyped_words, words[i]) == TYPE_SIM_FAILURE)
		{
			fprintf(fp, "%s\n", words[i].c_str());
		}
	}

	fclose(fp);

	return TYPE_SIM_SUCCESS;
}


int find_string(vector<string> words, string word)
{
	int ret = 0;
	for(unsigned int i = 0; i < words.size(); i++)
	{
		ret = words[i].compare(word);
		if(ret == 0)
		{
			/* return index */
			return i;
		}
		// printf("comparing %s and %s: %d\n", words[i].c_str(), word.c_str(), ret);
	}

	return TYPE_SIM_FAILURE;
} 