/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:29:06 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/22 14:34:51 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

void	exec_builtin(t_command **cmd, int pipe)
{
	if (pipe == YES)
		setup_pipe_outfile();
	else
		dup_outfile(cmd, YES);
	check_builtin((*cmd));
	close_files(cmd);
	reset_files();
}

/*Changes the command to lowercase to make sure it's useable, then
opens a pipe and creates a child. The signal is changed to make sure 
ctrl+c closes the child properly when a command is hanged. 
If we are in the child, we duplicate the infile and outfile of the 
command into the right STD_FILENO. Then, if the command is a builtin,
the associated function executes; else, execve takes charge of it
with the path.*/
void	child_two(t_command **cmd)
{
	int	*status;

	use_data()->pid = fork();
	signal(SIGINT, child_handler);
	signal(SIGQUIT, sigquit_handler);
	if (use_data()->pid == -1)
		pipex_error("minishell: fork: ", 1);
	else if (use_data()->pid == 0)
	{
		dup_infile(cmd, NO);
		dup_outfile(cmd, NO);
		execute(cmd);
		exit_program(0);
	}
	else
	{
		close_files(cmd);
		status = get_pid_status();
		set_exstat(status, 0);
		free(status);
	}
}

/*We duplicate the infile of the command as STDIN_FILENO and then we
duplicate the end of the pipe we want as the STDOUT_FILENO. Then, if 
the command is a builtin, the associated function executes; else, 
execve takes charge of it with the path.*/
void	child_one(t_command **cmd)
{
	int	i;

	dup_infile(cmd, YES);
	close(use_data()->fd[0]);
	if ((*cmd)->outfile == 1)
		setup_pipe_outfile();
	else
		dup_outfile(cmd, NO);
	i = 2;
	while (++i != 200)
		close(i);
	execute(cmd);
	exit_program(0);
}

/*Changes the command to lowercase to make sure it's useable, then
opens a pipe and creates a child. The signal is changed to make sure
ctrl+c closes the child properly when a command is hanged.
If we are in the child, then we use the execution function (child one).
If not, we close the end of the pipe we will not be using and store
the other end into the next command's infile fd.*/
void	pipex(t_command **cmd)
{
	if (pipe(use_data()->fd) < 0)
		pipex_error("minishell: pipe: ", 1);
	use_data()->pid = fork();
	signal(SIGINT, child_handler);
	signal(SIGQUIT, sigquit_handler);
	if (use_data()->pid == -1)
		pipex_error("minishell: fork: ", 1);
	else if (use_data()->pid == 0)
		child_one(cmd);
	else
	{
		close_files(cmd);
		close(use_data()->fd[1]);
		setup_pipe_infile(cmd);
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

	if (!cmd || !cmd->cmd)
		return ;
	nb_cmds = count_commands(cmd);
	if (nb_cmds == 1 && confirm_builtin(cmd))
		exec_single_builtin(cmd);
	else	
	{
		while (cmd->next)
		{
			pipex(&cmd);
			nb_cmds--;
			if (cmd->next)
				cmd = cmd->next;
		}
		child_two(&cmd);
		signal(SIGINT, interruption_handler);
	}
}
