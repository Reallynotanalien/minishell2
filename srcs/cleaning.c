
#include "../includes/minishell.h"

//To clean :
//When an error occurs : Nothing. It will be cleaned at the end of the loop.
//When the program exits :use_data()->cmd(arrays, close files, etc...), everything in use_data(), history, 
//When the loop finishes : use_data()->cmd(arrays, close files, etc...)

//Allocated in use_data() :
/*

use_data()->new_env(char **)
use_data()->line(char *)
use_data()->line_cpy(char *)
use_data()(t_data *)
*/

void	free_array(char ***array)
{
	int	i;

	i = -1;
	while (*array[++i])
	{
		free (*array[i]);
		*array[i] = NULL;
		i++;
	}
	free (*array);
	*array = NULL;
}

void	clean_cmds(void)
{
	t_command	*tmp;

	while (use_data()->cmd)
	{
		tmp = use_data()->cmd->next;
		if (use_data()->cmd->cmd)
			free_array(use_data()->cmd->cmd);
		if (use_data()->cmd->path)
		{
			free (use_data()->cmd->path);
			use_data()->cmd->path = NULL;
		}
		if (use_data()->cmd)
		{
			free (use_data()->cmd);
			use_data()->cmd = NULL;
		}
		use_data()->cmd = tmp;
	}
}

void	clean_tokens(void)
{
	t_command	*tmp;

	while (use_data()->token)
	{
		tmp = use_data()->token->next;
		if (use_data()->token->token)
			free (use_data()->token->token);
		if (use_data()->token)
		{
			free (use_data()->token);
			use_data()->token = NULL;
		}
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
		free_array (&(use_data()->new_env));
	if (use_data()->line)
		free (use_data()->line);
	if (use_data()->line_cpy)
		free (use_data()->line_cpy);
	free(use_data());
}

/*Clears the readline history and frees the data struct.*/
void	cleanup(void)
{
	rl_clear_history();
	clean_data();
}

