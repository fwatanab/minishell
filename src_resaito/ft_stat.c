#include "../inc/minishell.h"
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>

bool    able_read(char *filepath)
{
    struct stat buf;
    
    if (stat(filepath, &buf) < 0)
        return (true);
    if (buf.st_mode & S_IRUSR)
        return (true);
    return (false);
}

bool    able_write(char *filepath)
{
    struct stat buf;
    
    if (stat(filepath, &buf) < 0)
        return (true);
    if (buf.st_mode & S_IWUSR)
        return (true);
    return (false);
}

bool    able_exec(char *filepath)
{
    struct stat buf;
    
    if (stat(filepath, &buf) < 0)
        exit(1);
    if (buf.st_mode & S_IXUSR)
        return (true);
    return (false);
}
