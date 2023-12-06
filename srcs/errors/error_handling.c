
#include "../../includes/minishell.h"

//execve returns only if an error has occured. it then returns -1. Waitpid() can retrieve a child's return error.
/*        waitpid(pid, &status, 0); // Wait for the child process to finish
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
*/

void    set_error(char *source)
{
    use_data()->error_source = source;
}

//if errno was set, error_message should be NULL. Otherwise it means this is a custom error.
void    print_error(char *error_message)
{
    if (!error_message)
        perror(use_data()->error_source);
    else
        printf("%s\n", error_message);
}