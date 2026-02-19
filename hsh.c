#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ "), fflush(stdout);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			putchar('\n');
			return (0);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		pid = fork();
		if (pid == 0)
		{
			char *args[2];
			args[0] = line;
			args[1] = NULL;
			execve(line, args, environ);
			perror("./shell");
			exit(1);
		}
		else if (pid > 0)
		{
			int status;
			wait(&status);
		}
		else
		{
			perror("fork");
			exit(1);
		}
	}

	free(line);
	return (0);
}
