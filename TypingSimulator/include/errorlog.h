#ifndef _TYPING_SIMULATOR_ERRORLOG_H
#define _TYPING_SIMULATOR_ERRORLOG_H

#define ERROR_DB_FILE_NAME				"error.bin"
#define MISTYPED_WORDS_FILE_NAME		"mistyped_words.txt"
#define ERROR_CHAR_SET_SIZE				26

typedef struct{
	unsigned long long total_errors;
	unsigned long error_count[ERROR_CHAR_SET_SIZE];
}error_db;

typedef struct{
	error_db edb;
	char charset[ERROR_CHAR_SET_SIZE];
}error_stat;

int read_error_db(error_db* edb);
int write_error_db(error_db* edb);
void update_errors(error_db* edb, char error);
void display_errors_log();
void swap_char(char *a, char *b);
void swap_long(unsigned long *a, unsigned long *b);
void compute_error_stats(error_db* edb, error_stat* est);
void find_mistyped_words(vector<char>& input, vector<char>& text, vector<string>& mistyped_words);
void string_split(vector<char>& str, char c, vector<string>& words);
void print_words(vector<string>& words);
int write_mistyped_words(vector<string>& words);
int read_mistyped_words(vector<string>& words);
int find_string(vector<string> words, string word);

#endif /* _TYPING_SIMULATOR_ERRORLOG_H */
