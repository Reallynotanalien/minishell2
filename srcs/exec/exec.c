/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:29:06 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 11:56:19 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	dup_fds(t_command *cmd)
{
	if (cmd->outfile == STDOUT_FILENO && cmd->next)
		dup2(cmd->pipe_cmd[1], STDOUT_FILENO);
	else if (cmd->outfile != STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close (cmd->outfile);
	}
	// if (cmd->infile != STDIN_FILENO)
	// {
		// dup2(cmd->infile, STDIN_FILENO);
		// close (cmd->infile);
	// }
	close_pipes(cmd->pipe_cmd);
}

void	handle_child(t_command *cmd)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, sigquit_handler);
	ft_printf(2, "In child pipe[0] : %d pipe[1] : %d infile : %d outfile : %d\n", cmd->pipe_cmd[0], cmd->pipe_cmd[1], cmd->infile, cmd->outfile);
	dup_fds(cmd);
	execute(cmd);
	exit_program(use_data()->exstat);
}

int	setup_pipes(t_command *cmd)
{
	if (pipe(cmd->pipe_cmd) < 0)
	{
		perror("minishell: pipe: ");
		return (1);
	}
	return (0);
}

void	exec(t_command *cmd)
{
	int	nb_cmds;

	if (!cmd || !cmd->cmd)
		return ;
	nb_cmds = count_commands(cmd);
	if (nb_cmds == 1 && confirm_builtin(cmd))
		return (exec_single_builtin(cmd));
	while (cmd)
	{
		setup_pipes(cmd);
		use_data()->pid = fork();
		if (use_data()->pid == -1)
			return (perror("minishell: fork: "));
		else if (use_data()->pid == 0)
			handle_child(cmd);
		dup_infile(cmd);
		close_pipes(cmd->pipe_cmd);
		if (cmd->outfile != STDOUT_FILENO)
			close (cmd->outfile);
		cmd = cmd->next;
	}
	dup2(use_data()->old_stdin, 0);
	dup2(use_data()->old_stdout, 1);
	get_pid_status();
}
