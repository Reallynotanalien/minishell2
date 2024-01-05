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
void	dup_infile(t_command **cmd, int copy)
{
	if ((*cmd)->infile != STDIN_FILENO)
	{
		if (copy == YES)
			dup2(STDIN_FILENO, use_data()->old_stdin);
		dup2((*cmd)->infile, STDIN_FILENO);
		close((*cmd)->infile);
	}
}

/*If the outfile is different than the STDOUT_FILENO, the
STDOUT_FILENO gets replaced by the outfile.*/
void	dup_outfile(t_command **cmd, int copy)
{
	if ((*cmd)->outfile != STDOUT_FILENO)
	{
		if (copy == YES)
			dup2(STDOUT_FILENO, use_data()->old_stdout);
		dup2((*cmd)->outfile, STDOUT_FILENO);
		close((*cmd)->outfile);
	}
}

void	setup_pipe_outfile(void)
{
	dup2(use_data()->fd[1], STDOUT_FILENO);
	close(use_data()->fd[1]);
}

/*Resets the STDIN_FILENO and STDOUT_FILENO to the original
ones in case a dup2 was used.*/
void	reset_files(void)
{
	dup2(use_data()->old_stdout, STDOUT_FILENO);
	if (STDIN_FILENO != 0)
		dup2(use_data()->old_stdin, STDIN_FILENO);
}

void	setup_pipe_infile(t_command **cmd)
{
	if (!confirm_builtin((*cmd)->next))
		(*cmd)->next->infile = use_data()->fd[0];
	else
		close(use_data()->fd[0]);
}
