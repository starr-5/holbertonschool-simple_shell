#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    extern char **environ;

    while (1)
    {
        /* Show prompt only if stdin is terminal */
        if (isatty(STDIN_FILENO))
            printf("#cisfun$ "), fflush(stdout);

        nread = getline(&line, &len, stdin);

        /* Handle Ctrl+D or EOF */
        if (nread == -1)
        {
            free(line);
            putchar('\n');
            exit(0);
        }

        /* Remove newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        pid = fork();
        if (pid == 0)
        {
            char *argv[] = {line, NULL};
            execve(line, argv, environ);
            perror("./shell"); /* Command not found */
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
