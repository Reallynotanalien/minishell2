/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:26:58 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 11:44:28 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exstat(int *status, int exstat)
{
	if (!status)
		use_data()->exstat = exstat;
	else if (WIFEXITED(*status))
		use_data()->exstat = WEXITSTATUS(*status);
	else
		if (WIFSIGNALED(*status))
			use_data()->exstat = WTERMSIG(*status) + 128;
}

int	get_pid_status(void)
{
	int	status;

	waitpid(use_data()->pid, &status, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (status);
}
