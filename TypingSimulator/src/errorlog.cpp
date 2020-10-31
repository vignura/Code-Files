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

#if 0
void display_errors_log()
{
	int index = 0;
	error_db edb = {0};
	char charset[ERROR_CHAR_SET_SIZE] = {0};

	/* intialse the charset with alphabets */
	for(index = 0; index < ERROR_CHAR_SET_SIZE; index++)
	{
		charset[index] = ('a' + index);
	}

	printf("ERROR STATS\n");

	/* read error db */
	if(read_error_db(&edb) == TYPE_SIM_SUCCESS)
	{
		/* sort descending */
		for(int i = 0; i < ERROR_CHAR_SET_SIZE; i++)
		{	
			for(int j = (i +1); j < ERROR_CHAR_SET_SIZE; j++)
			{
				if(edb.error_count[i] < edb.error_count[j])
				{
					swap_char(&charset[i], &charset[j]);
					swap_long(&edb.error_count[i], &edb.error_count[j]);
				}
			}
		}

		for(index = 0; index < ERROR_CHAR_SET_SIZE; index++)
		{
			printf("%c: %ld (%.02f)\n", charset[index], edb.error_count[index],
				  (((double)edb.error_count[index] / (double)edb.total_errors) * 100));
		}

		printf("total errors: %lld\n", edb.total_errors);
	}
	else
	{
		printf("unable to display error log\n");
	}
}
#else
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
#endif

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
