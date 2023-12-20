# include "../../includes/minishell.h"

/*If an error is found in the parsing, an error message gets
printed and the error flag gets turned on. The parsing can then 
continue and print as many error messages as it needs without exiting
the program; the flag will get catched at the moment of the execution.*/
int	parsing_error(char *error)
{
	printf("minishell: %s", error);
	use_data()->error_flag = ERROR;
	return (ERROR);
}

/*Gracefully exits the program by cleaning up all necessary data
before printing an exit message, restoring the terminal's original
attributes and exiting.*/
void	exit_program(int code)
{
	cleanup();
	restore_attributes();
	exit(code);
}

void	heredoc_error(char *error, int status)
{
	ft_printf(2, error);
	use_data()->error_flag = ERROR;
	set_exstat(NULL, status);
}

int	*get_pid_status(void)
{
	int	*status;

	status = ft_calloc(1, sizeof(int));
	waitpid(use_data()->pid, status, 0);
	return (status);
}
