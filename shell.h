#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* to read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* to command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* to convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: it is the number field
 * @str: it is a string
 * @next: it points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains arguements to pass into a function
 * @line_count: it is the error count
 * @err_num: it is the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: it is the program filename
 * @env: it is linked list local copy of environ
 * @arg: string generated from getline containing arguements
 * @argv: array of strings generated from arg
 * @path: string path for the current command
 * @argc: it is the argument count
 * @environ: it is custom modified copy of environ from LL env
 * @history: it is the history node
 * @alias: it is the alias node
 * @env_changed: on if environ was changed
 * @status: it is the return status of the last exec'd command
 * @cmd_buf: it is address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: it is the fd from which to read line input
 * @histcount: it is the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - it contains a builtin string and related function
 * @type: it is the builtin command flag
 * @func: it is the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int find_builtin(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _eputchar(char);

/* toem_string.c */
int _strlen(char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
void _puts(char *);
int _putchar(char);
char *_strdup(const char *);

/* toem_exits.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int _isalpha(int);
int _atoi(char *);
int is_delim(char, char *);

/* toem_errors1.c */
int _erratoi(char *);
char *convert_number(long int, int, int);
void remove_comments(char *);
void print_error(info_t *, char *);
int print_d(int, int);

/* toem_builtin.c */
int _myhelp(info_t *);
int _myexit(info_t *);
int _mycd(info_t *);

/* toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/*toem_getline.c */
void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

/* toem_getinfo.c */
void free_info(info_t *, int);
void clear_info(info_t *);
void set_info(info_t *, char **);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);

/* toem_getenv.c */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/* toem_history.c */
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);

/* toem_lists1.c */
size_t list_len(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);

#endif
