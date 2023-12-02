
#include "../includes/minishell.h"

//To clean :
//When an error occurs : Nothing. It will be cleaned at the end of the loop.
//When the program exits :use_data()->cmd(arrays, close files, etc...), everything in use_data(), history, 
//When the loop finishes : use_data()->cmd(arrays, close files, etc...)

//Allocated in use_data() :
/*

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
