#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

/* for read/write buffers */
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - its singly linked list
 * @num: it is the number field
 * @str: its a string
 * @next: will point to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - will contain arguements to pass into function
 * @arg: its string generated from getline containing arguements
 * @argv:its an array of strings generated from arg
 * @path: it is string path for the current command
 * @argc: it is the argument count
 * @line_count: it is the error count
 * @err_num: it is the error code for exit()
 * @linecount_flag: if on count this line of input
 * @fname: it is the program filename
 * @env: it is linked list local copy of environ
 * @environ: it is custom modified copy of environ from LL env
 * @history: it is the history node
 * @alias: it is the alias node
 * @env_changed: if environ was changed its on
 * @status: its the return status of the last exec'd command
 * @cmd_buf: it is address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: the CMD_type ||, &&, ;
 * @readfd: it is the fd from which to read line input
 * @histcount: it is the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	int argc;
	unsigned int line_count;
	char *path;
	int err_num;
	char *fname;
	list_t *history;
	list_t *env;
	char **environ;
	int env_changed;
	int status;
	int linecount_flag;
	list_t *alias;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
void fork_cmd(info_t *);
void find_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

/* toem_parser.c */
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
void _eputs(char *);
int _eputchar(char);

/* toem_string.c */
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strlen(char *);
char *starts_with(const char *, const char *);

/* toem_string1.c */
void _puts(char *);
int _putchar(char);
char *_strdup(const char *);
char *_strcpy(char *, char *);

/* toem_exits.c */
char *_strchr(char *, char);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_realloc.c */
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int _atoi(char *);
int interactive(info_t *);
int _isalpha(int);
int is_delim(char, char *);

/* toem_errors1.c */
int print_d(int, int);
void print_error(info_t *, char *);
void remove_comments(char *);
char *convert_number(long int, int, int);
int _erratoi(char *);

/* toem_builtin.c */
int _myhelp(info_t *);
int _myexit(info_t *);
int _mycd(info_t *);

/* toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/*toem_getline.c */
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);

/* toem_getinfo.c */
void free_info(info_t *, int);
void set_info(info_t *, char **);
void clear_info(info_t *);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node_end(list_t **, const char *, int);
list_t *add_node(list_t **, const char *, int);
void free_list(list_t **);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);

/* toem_vars.c */
int replace_alias(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);

#endif
