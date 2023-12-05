# include "../../includes/minishell.h"

/*Iterates through the command struct to find out how many there
are, and returns it.*/
int	count_commands(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->next)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

/*If the infile is different than the STDIN_FILENO, the 
STDIN_FILENO gets replaced by the infile.*/
void	dup_infile(t_command **cmd)
{
	if ((*cmd)->infile != STDIN_FILENO)
	{
		dup2((*cmd)->infile, STDIN_FILENO);
		close((*cmd)->infile);
	}
}

/*If the outfile is different than the STDOUT_FILENO, the
STDOUT_FILENO gets replaced by the outfile.*/
void	dup_outfile(t_command **cmd)
{
	if ((*cmd)->outfile != STDOUT_FILENO)
	{
		dup2((*cmd)->outfile, STDOUT_FILENO);
		close((*cmd)->outfile);
	}
}