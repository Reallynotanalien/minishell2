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



void	clean_data(void)
{
	if (use_data()->token)
		free (use_data()->token);
	if (use_data())
		free (use_data());
}

/*Clears the readline history and frees the data struct.*/
void	cleanup(void)
{
	rl_clear_history();
	clean_data();
}

int	print_error(char *message)
{
	printf("%s\n", message);
	return (ERROR);
}

/*Gracefully exits the program by cleaning up all necessary data
before printing an exit message, restoring the terminal's original
attributes and exiting.*/
void	exit_program(int code)
{
	cleanup();
	//printf to be deleted later on
	// printf("Cleanup done!\n");
	// restore_attributes();
	exit(code);
}

//Used to indicate an error, to be replaced by proper error printing and handling.
void	tmp_error(char *error_message)
{
	printf("tmp error : %s", error_message);
}
