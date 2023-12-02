//execve returns only if an error has occured. it then returns -1. Waitpid() can retrieve a child's return error.
/*        waitpid(pid, &status, 0); // Wait for the child process to finish
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
*/