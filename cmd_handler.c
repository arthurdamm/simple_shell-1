#include "shell.h"

/**
  * built_in_handler - handles built in fncs
  * @argv: argument vector
  * @env: environment linked list
  * @i: switch for built-ins
  */
void built_in_handler(char **argv, env_list_t **env, int i)
{
	switch (i)
	{
		case 0:
			_cd(argv, env);
			break;
		case 1:
			_setenv_list(argv, env);
			break;
		case 2:
			_unsetenv_list(argv, env);
			break;
		case 3:
			printenv_list(env);
			break;
	}
}

/**
  * cmd_handler - handles all commands
  * @argv: argument vector
  * @env: environment linked list
  * Return: 0 on failure, 1 on true
  */
int cmd_handler(char **argv, env_list_t **env)
{
	char *built_ins[] = {"cd", "setenv", "unsetenv", "env", NULL};
	int i, status;
	struct stat st;
	char *path_to_file;
	pid_t child_pid;
	char **str_env = _get_str_env(env);

	/* if it's a buitin */
	for (i = 0; built_ins[i]; i++)
	{
		if (!_strcmp(built_ins[i], argv[0]))
		{
			built_in_handler(argv, env, i);
			double_free(str_env);
			return (1);
		}
	}

	/* if it's a full-path cmd */
	/* else if it can be found in the PATH */
	/* else it must not be a cmd */
	if (stat(argv[0], &st) == 0)
		path_to_file = argv[0];
	else
	{
		path_to_file = whitcher(argv[0], env);
	}
	if (path_to_file && _strcmp(path_to_file, _getenv_list_value("PATH", env)))
	{
		path_to_file = _strcat(path_to_file, "/");
		path_to_file = _strcat(path_to_file, argv[0]);
	}
	else
	{
		printf("%s: command not found\n", argv[0]);
		double_free(str_env);
		return (0);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (0);
	}
	if (child_pid == 0)
	{
		if (execve(path_to_file, argv, str_env) == -1)
			perror("Error:");
		exit(0);
	}
	wait(&status);
	double_free(str_env);
	/*
	free(path_to_file);
*/
	return (1);
}
