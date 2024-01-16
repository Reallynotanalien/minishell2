/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:28:55 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/16 13:49:01 by edufour          ###   ########.fr       */
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

void	close_files(t_command **cmd)
{
	if ((*cmd)->infile != 0)
		close((*cmd)->infile);
	if ((*cmd)->outfile != 1)
		close((*cmd)->outfile);
}

void	execute(t_command **cmd)
{
	if (!check_builtin((*cmd)))
	{
		if (execve((*cmd)->path, (*cmd)->cmd, use_data()->new_env))
		{
			ft_printf(2, "minishell: %s: command not found\n", (*cmd)->cmd[0]);
			exit_program(127);
		}
	}
}
