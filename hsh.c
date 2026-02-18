#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * main - simple shell
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	int status;

	while (1)
	{
		printf("$ ");

		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			exit(0);
		}

		pid = fork();

		if (pid == 0)
		{
			char *argv[] = {line, NULL};

			execve(line, argv, NULL);
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
