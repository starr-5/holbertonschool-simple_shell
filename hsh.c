#include "shell.h"

void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}

char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		if (isatty(STDIN_FILENO))
			printf("\n");
		exit(0);
	}

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return line;
}

void execute_line(char *line)
{
	pid_t pid;
	int status;

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
		perror("./shell");
		exit(1);
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - simple shell
 * Return: 0
 */
int main(void)
{
	char *line;

	while (1)
	{
		print_prompt();
		line = read_line();
		execute_line(line);
		free(line);
	}

	return (0);
}
