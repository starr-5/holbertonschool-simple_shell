#include "shell.h"

/**
 * main - simple shell
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		/* Show prompt only if stdin is terminal */
		if (isatty(STDIN_FILENO))
		{
			printf("#cisfun$ ");
			fflush(stdout);
		}

		/* Read a line from stdin */
		nread = getline(&line, &len, stdin);

		/* Handle Ctrl+D or EOF */
		if (nread == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(0);
		}

		/* Remove newline */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			exit(1);
		}

		if (pid == 0)
		{
			char *argv[] = {line, NULL};

			execve(line, argv, environ);
			perror("./shell"); /* Command not found */
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
