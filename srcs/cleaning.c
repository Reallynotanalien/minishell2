
#include "../includes/minishell.h"

//To clean :
//When an error occurs : Nothing. It will be cleaned at the end of the loop.
//When the program exits :use_data()->cmd(arrays, close files, etc...), everything in use_data(), history, 
//When the loop finishes : use_data()->cmd(arrays, close files, etc...)

//Allocated in use_data() :
/*
use_data()->cmd->cmd(char **)
use_data()->cmd->path(char *)
use_data()->cmd(t_command *)
use_data()->token->token(char *)
use_data()->token(t_token *)
use_data()->new_env(char **)
use_data()->line(char *)
use_data()->line_cpy(char *)
use_data()(t_data *)
*/
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
