
#include "../includes/minishell.h"

//To clean :
//When an error occurs : Nothing. It will be cleaned at the end of the loop.
//When the program exits :use_data()->cmd(arrays, close files, etc...), 
//everything in use_data(), history, 
//When the loop finishes : use_data()->cmd(arrays, close files, etc...)

//Allocated in use_data() :
/*

use_data()->new_env(char **)
use_data()->line(char *)
use_data()->line_cpy(char *)
use_data()(t_data *)
*/

void	clean_after_loop(void)
{
	free(use_data()->line);
	clean_cmds();
	free (use_data()->line_cpy);
	use_data()->line_cpy = NULL;
	if (use_data()->heredoc_flag == YES)
		unlink(".here_doc");
}

void	clean_cmds(void)
{
	t_command	*tmp;

	while (use_data()->cmd)
	{
		tmp = use_data()->cmd->next;
		free_array(use_data()->cmd->cmd);
		free (use_data()->cmd->path);
		free(use_data()->cmd->lower_cmd);
		free(use_data()->cmd);
		use_data()->cmd = tmp;
	}
}

void	clean_tokens(void)
{
	t_token	*tmp;

	while (use_data()->token)
	{
		tmp = use_data()->token->next;
		safe_free ((void **)&use_data()->token->token);
		safe_free ((void **)&use_data()->token);
		use_data()->token = tmp;
	}
}

//Used to clean the entirety of use_data()
void	clean_data(void)
{
	if (use_data()->cmd)
		clean_cmds();
	if (use_data()->token)
		clean_tokens();
	if (use_data()->new_env)
		free_array(use_data()->new_env);
	safe_free ((void **)&use_data()->line);
	safe_free ((void **)&use_data()->line_cpy);
	if (use_data())
		free (use_data());
}

/*Clears the readline history and frees the data struct.*/
void	cleanup(void)
{
	rl_clear_history();
	clean_data();
}
