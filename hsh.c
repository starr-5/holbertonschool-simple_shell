#include "shell.h"

/**
 * print_prompt - prints shell prompt
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}

/**
 * read_line - reads a line from stdin
 * Return: pointer to line string
 */
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

	return (line);
}

/**
 * execute_line - forks and executes a command line
 * @line: command line string
 */
void execute_line(char *line)
{
	pid_t pid;
	int status;
	char *argv[2]; /* fix for pedantic C89/gnu89 */

	argv[0] = line;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(line);
		exit(1);
	}

	if (pid == 0)
	{
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
