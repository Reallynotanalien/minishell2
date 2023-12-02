# include "../../includes/minishell.h"

void	child_two(t_command **cmd)
{
	(*cmd)->cmd[0] = ft_strlower((*cmd)->cmd[0]);
	use_data()->pid = fork();
	signal(SIGINT, child_handler);
	if (use_data()->pid == -1)
		printf("FORK did not work\n");
	else if (use_data()->pid == 0)
	{
		dup_infile(cmd);
		dup_outfile(cmd);
		if (!check_builtin((*cmd)->cmd))
			execve(get_path(*cmd), (*cmd)->cmd, use_data()->new_env);
		exit(0);
	}
	else
		waitpid(use_data()->pid, NULL, 0);
}

void	child_one(t_command **cmd)
{
	dup_infile(cmd);
	close(use_data()->fd[0]);
	dup2(use_data()->fd[1], STDOUT_FILENO);
	close(use_data()->fd[1]);
	if (!check_builtin((*cmd)->cmd))
		execve(get_path(*cmd), (*cmd)->cmd, use_data()->new_env);
	exit(0);
}

void	pipex(t_command **cmd)
{
	(*cmd)->cmd[0] = ft_strlower((*cmd)->cmd[0]);
	if (pipe(use_data()->fd) < 0)
		printf("PIPE did not work\n");
	use_data()->pid = fork();
	signal(SIGINT, child_handler);
	if (use_data()->pid == -1)
		printf("FORK did not work\n");
	else if (use_data()->pid == 0)
		child_one(cmd);
	else
	{
		close(use_data()->fd[1]);
		(*cmd)->next->infile = use_data()->fd[0];
	}
}

/*Counts the number of commands in the struct, and uses pipex
until the last command to open pipes and execute them. Then, 
executes the last command separately (if there is only one
command, it will jump right to this point) and when all is 
done, the signal handler is reset to the main handler.*/
void	exec(t_command *cmd)
{
	int	nb_cmds;

	nb_cmds = count_commands(cmd);
	while (cmd && nb_cmds > 1)
	{
		pipex(&cmd);
		nb_cmds--;
		if (cmd->next)
			cmd = cmd->next;
	}
	child_two(&cmd);
	signal(SIGINT, interruption_handler);
}
