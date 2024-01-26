/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:29:06 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/26 18:36:40 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "../../includes/minishell.h"

void	dup_fds(t_command *cmd)
{
	if (cmd->infile == STDIN_FILENO && cmd->prev)
		dup2(cmd->prev->pipe_cmd[0], STDIN_FILENO);
	else if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close (cmd->infile);
	}
	if (cmd->next && cmd->outfile == STDOUT_FILENO)
		dup2(cmd->pipe_cmd[1], STDOUT_FILENO);
	else if (cmd->outfile != STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close (cmd->outfile);
	}
	close (cmd->prev->pipe_cmd[0]);
	close (cmd->prev->pipe_cmd[1]);
	close (cmd->pipe_cmd[0]);
	close (cmd->pipe_cmd[1]);
}

void	handle_child(t_command *cmd)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, sigquit_handler);
	ft_printf(2, "pipe[0] : %d pipe[1] : %d infile : %d outfile : %d\n", cmd->pipe_cmd[0], cmd->pipe_cmd[1], cmd->infile, cmd->outfile);
	dup_fds(cmd);
	execute(cmd);
}

int	setup_pipes(t_command *cmd)
{
	if (cmd->next && pipe(cmd->pipe_cmd) < 0)
	{
		perror("minishell: pipe: ");
		return (1);
	}
	return (0);
}

void	close_pipes(t_command *cmd)
{
	if (cmd->prev)
	{
		close(cmd->prev->pipe_cmd[0]);
		close(cmd->prev->pipe_cmd[1]);
	}	
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
		else
		{
			close_pipes(cmd);
			if (cmd->prev && cmd->prev->prev)
			{
				close(cmd->prev->prev->pipe_cmd[0]);
				close(cmd->prev->prev->pipe_cmd[1]);
			}
			cmd = cmd->next;
		}
	}
	get_pid_status();
}
