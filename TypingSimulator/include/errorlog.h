#ifndef _TYPING_SIMULATOR_ERRORLOG_H
#define _TYPING_SIMULATOR_ERRORLOG_H

#define ERROR_DB_FILE_NAME		"error.bin"
#define ERROR_CHAR_SET_SIZE		26

typedef struct{
	unsigned long long total_errors;
	unsigned long error_count[ERROR_CHAR_SET_SIZE];
}error_db;

int read_error_db(error_db* edb);
int write_error_db(error_db* edb);
void update_errors(error_db* edb, char error);
void display_errors_log();

#endif /* _TYPING_SIMULATOR_ERRORLOG_H */