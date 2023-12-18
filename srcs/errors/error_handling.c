
#include "../../includes/minishell.h"

//execve returns only if an error has occured. it then returns -1. Waitpid() can retrieve a child's return error.
/*        waitpid(pid, &status, 0); // Wait for the child process to finish
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
*/

//if errno was set, error_message should be NULL. Otherwise it means this is a custom error.
void    print_error(char *src, char *cmd, char *error, int perror_flag, int exstat)
{
    write(STDERR_FILENO, src, ft_strlen(src));
    if (perror_flag)
        perror(cmd);
    else if (cmd)
    {
        write(STDERR_FILENO, cmd, ft_strlen(cmd));
        write(STDERR_FILENO, ": ", 2);
    }
    if (error)
        write(STDERR_FILENO, error, ft_strlen(error));
    if (!perror_flag)
        write(STDERR_FILENO, "\n", 1);
    use_data()->exstat = exstat;
}