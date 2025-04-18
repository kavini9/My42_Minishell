#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int ac, char **av)
{
    char *cmd[] = {av[1], av[2], NULL};
    char *env[] = {NULL};

    if (access(av[1], F_OK == 0))
    {
        if (access(av[1], X_OK) == 0)
        {
            if (execve(cmd[0], cmd, env) == -1)
            {
                fprintf(stderr, "minishell: %s: %s\n", cmd[0], strerror(errno));
                if (errno == ENOENT)
                    exit(127);
                else
                    exit(126);
            }
        }
        else
            fprintf(stderr, "acceess X_OK: %s: %s\n", cmd[0], strerror(errno));
    }
    else
        fprintf(stderr, "acceess F_OK: %s: %s\n", cmd[0], strerror(errno));
    

    return 0;
}