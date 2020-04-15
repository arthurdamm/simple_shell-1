#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>

/* this just does in one line: free(x); x = NULL; */
#define FREE(x) (x = (free(x), NULL))

/* structs */
/**
  * struct order - struct to contain &&'s and ||'s
  * @n: coded int, 1 = ; , 2 = && , 3 = ||
  * @next: points to the next node
  */
typedef struct order
{
	unsigned int n;
	struct order *next;
} order_t;
/**
  * struct env_list - struct to contain env
  * @name: name of env var
  * @value: value of env var
  * @next: points to the next node
  */
typedef struct env_list
{
	char *name;
	char *value;
	struct env_list *next;
} env_list_t;

/* getline */
int _getline(char **lineptr, size_t *n, FILE *stream);

/* memory helpers */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* string helpers */
int _atoi(char *s);
int _strlen(char *str);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strtok(char *input, char *delim);
char *_strchr(char *s, char c);

/* cmd_handler */
int cmd_handler(char **argv, env_list_t **env);
void built_in_handler(char **argv, env_list_t **env, int i);
void _cd(char **argv, env_list_t **env);

/* cmd assembly */
char **get_tokens(char *str_tok, char *delim);
int isin_dir(char *term, char *dir);
char *whitcher(char *cmd, env_list_t **env);
void rem_comments(char *str);
void double_free(char **argv);

/* env variable */
char **_initenv(void);
void _setenv(char **argv, char ***env);
void _unsetenv(char *entry, char ***env);
char *_getenv(char *entry, char ***env);
void _printenv(char ***env);

/* env_list */
env_list_t **_initenv_list(void);
void printenv_list(env_list_t **env);
char *_getenv_list_value(char *name, env_list_t **env);
env_list_t *_getenv_list_node(char *name, env_list_t **env);
void _setenv_list(char **argv, env_list_t **env);
void free_env_list_node(env_list_t *node);
void _unsetenv_list(char **argv, env_list_t **env);
void free_env_list(env_list_t **env);
char **_get_str_env(env_list_t **env);

/* ops */
void *op_push_end(order_t **ops, int n);
char **_get_cmds(char *line, order_t **ops);
void free_ops(order_t **ops);

extern char **environ;
#endif /* SHELL */
