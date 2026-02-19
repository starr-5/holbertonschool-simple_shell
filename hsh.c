#include "shell.h"

extern char **environ;

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
		printf("$ ");
		fflush(stdout);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(0);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			free(line);
			exit(1);
		}

		if (pid == 0)
		{
			char *argv[] = {line, NULL};

			execve(line, argv, environ);
			perror("Error");
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}

	return (0);
}
