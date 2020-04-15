#include "shell.h"

/**
  * whitcher - locates cmd's in the PATH
  * @cmd: char * containing the cmd
  * @env: environment linked list
  * Return: dir file is in or full path (change this to NULL
  */
char *whitcher(char *cmd, env_list_t **env)
{
	char *PATH = _getenv_list_value("PATH", env);
	/* we need to keep PATH_COPY ptr to free it after the strdup */
	char *PATH_COPY = _strdup(PATH);
	/* sometimes we "cheat" with a static char buf which need not be freed
	   I did this here also because it turns out cmd_handler() tries to
	   _strcat on this string so we need to give it extra space */
	static char buf[256];
	char **tokens;
	int i;

	tokens = get_tokens(PATH_COPY, ":");

	for (i = 0; tokens[i]; i++)
	{
		/* if cmd is in the directory passed by tokens[i] */
		/* then return the dir */
		if (isin_dir(cmd, tokens[i]))
		{
			/* we need to "duplicate" just this token by copying it to the static buf
			which has extra spaces for more concatenation in cmd_handler() */
			buf[0] = 0; /* empty buffer */
			_strcat(buf, tokens[i]);
			FREE(PATH_COPY);
			free(tokens);
			return (buf);
		}
	}
	FREE(PATH_COPY);
	free(tokens);
	return (NULL);
}
