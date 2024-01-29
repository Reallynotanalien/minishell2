/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:28:55 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 12:00:15 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	execute(t_command *cmd)
{
	if (!check_builtin(cmd))
	{
		if (execve(cmd->path, cmd->cmd, use_data()->new_env))
		{
			ft_printf(2, "minishell: %s: command not found\n", cmd->cmd[0]);
			exit_program(127);
		}
	}
}

void	exec_single_builtin(t_command *cmd)
{
	if (cmd->infile != STDIN_FILENO)
		dup2(cmd->infile, STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO);
	check_builtin(cmd);
}
