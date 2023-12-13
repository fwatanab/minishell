#include "../inc/minishell.h"
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>

bool    able_read(char *filepath)
{
    struct stat buf;
    
    if (stat(filepath, &buf) < 0)
        exit(1);
    if (buf.st_mode & S_IRUSR)
    {
        printf("read true\n");
        return (true);
    }
    printf("read false\n");
    return (false);
}

bool    able_write(char *filepath)
{
    struct stat buf;
    
    if (stat(filepath, &buf) < 0)
        exit(1);
    if (buf.st_mode & S_IWUSR)
    {
        printf("write true\n");
        return (true);
    }
    printf("write false\n");
    return (false);
}

int    able_file(char *filepath, t_redir *redir)
{
    t_redir *tmp;

    if (!redir)
        return(0);
    tmp = redir;
    while (tmp)
    {
        if ((tmp->type == N_REDIR_IN && !able_read(filepath)) ||
            ((tmp->type == N_REDIR_OUT || tmp->type == N_REDIR_APPEND)
            && !able_write(filepath)))
            return(print_error(tmp->file, "Permission denied", 1));
        tmp = tmp->next;
    }
    return (0);
}