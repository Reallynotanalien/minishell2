/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:27:38 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 12:01:01 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*If the infile is different than the STDIN_FILENO, the 
STDIN_FILENO gets replaced by the infile.*/
void	dup_infile(t_command *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	else
		dup2(cmd->pipe_cmd[0], STDIN_FILENO);
}
