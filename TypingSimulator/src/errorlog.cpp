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

void display_errors_log()
{
	int index = 0;
	error_db edb = {0};

	printf("ERROR STATS\n");
	
	/* read error db */
	if(read_error_db(&edb) == TYPE_SIM_SUCCESS)
	{
		for(index = 0; index < ERROR_CHAR_SET_SIZE; index++)
		{
			printf("%c: %ld (%.02f)\n", ('a' + index), edb.error_count[index],
				  (((double)edb.error_count[index] / (double)edb.total_errors) * 100));
		}

		printf("total errors: %lld\n", edb.total_errors);
	}
	else
	{
		printf("unable to display error log\n");
	}
}