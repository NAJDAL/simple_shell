#ifndef _CUSTOM_SHELL_H_
#define _CUSTOM_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Constants for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Constants for command chaining */
#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Constants for converting numbers */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Use system getline function */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".custom_shell_history"
#define MAX_HISTORY_ENTRIES 4096

extern char **custom_environ;

/**
 * struct StringList - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct StringList
{
    int num;
    char *str;
    struct StringList *next;
} StringList_t;

/**
 * struct CommandInfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()
 * @linecount_flag: if on, count this line of input
 * @fname: the program filename
 * @env: linked list local copy of custom_environ
 * @history: the history node
 * @env_changed: on if custom_environ was changed
 * @status: the return status of the last executed command
 */
typedef struct CommandInfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    StringList_t *env;
    StringList_t *history;
    int env_changed;
    int status;
} CommandInfo_t;

#define COMMAND_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, 0, 0}

/**
 * struct BuiltInCommand - contains a built-in string and related function
 * @type: the built-in command flag
 * @func: the function
 */
typedef struct BuiltInCommand
{
    char *type;
    int (*func)(CommandInfo_t *);
} BuiltInCommand_t;

/* toem_shloop.c */
int custom_shell(CommandInfo_t *, char **);
int find_builtin(CommandInfo_t *);
void find_command(CommandInfo_t *);
void fork_command(CommandInfo_t *);

/* toem_parser.c */
int is_command(CommandInfo_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(CommandInfo_t *, char *, char *);

/* loophsh.c */
int custom_shell_loop(char **);

/* toem_errors.c */
void error_puts(char *);
int error_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* toem_string.c */
int string_length(char *);
int string_compare(char *, char *);
char *starts_with(const char *, const char *);
char *string_concat(char *, char *);

/* toem_string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void custom_puts(char *);
int custom_putchar(char);

/* toem_exits.c */
char *string_n_copy(char *, char *, int);
char *string_n_concat(char *, char *, int);
char *string_character(char *, char);

/* toem_tokenizer.c */
char **string_tokenize(char *, char *);
char **string_tokenize2(char *, char);

/* toem_realloc.c */
char *memory_set(char *, char, unsigned int);
void free_strings(char **);
void *memory_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int buffer_free(void **);

/* toem_atoi.c */
int interactive_command(CommandInfo_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_integer(char *);

/* toem_errors1.c */
int string_to_integer_error(char *);
void print_custom_error(CommandInfo_t *, char *);
int print_decimal(int, int);
char *convert_integer(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int custom_exit(CommandInfo_t *);
int custom_cd(CommandInfo_t *);
int custom_help(CommandInfo_t *);

/* toem_builtin1.c */
int custom_history(CommandInfo_t *);
int custom_alias(CommandInfo_t *);

/* toem_getline.c */
ssize_t get_input(CommandInfo_t *);
int custom_getline(CommandInfo_t *, char **, size_t *);
void sigint_handler(int);

/* toem_getinfo.c */
void clear_command_info(CommandInfo_t *);
void set_command_info(CommandInfo_t *, char **);
void free_command_info(CommandInfo_t *, int);

/* toem_environ.c */
char *_getenv(CommandInfo_t *, const char *);
int _myenv(CommandInfo_t *);
int _mysetenv(CommandInfo_t *);
int _myunsetenv(CommandInfo_t *);
int populate_env_list(CommandInfo_t *);

/* toem_getenv.c */
char **get_custom_environ(CommandInfo_t *);
int _unsetenv(CommandInfo_t *, char *);
int _setenv(CommandInfo_t *, char *, char *);

/* toem_history.c */
char *get_history_file(CommandInfo_t *info);
int write_history(CommandInfo_t *info);
int read_history(CommandInfo_t *info);
int build_history_list(CommandInfo_t *info, char *buf, int linecount);
int renumber_history(CommandInfo_t *info);

/* toem_lists.c */
StringList_t *add_node(StringList_t **, const char *, int);
StringList_t *add_node_end(StringList_t **, const char *, int);
size_t print_list_str(const StringList_t *);
int delete_node_at_index(StringList_t **, unsigned int);
void free_list

/* toem_vars.c */
int is_command_chain(info_t *, char *, size_t *);
void process_command_chain(info_t *, char *, size_t *, size_t, size_t);
int substitute_alias(info_t *);
int substitute_variables(info_t *);
int substitute_string(char **, char *);

#endif
