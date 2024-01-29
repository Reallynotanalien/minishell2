/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:26:58 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 16:07:06 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exstat(int exstat)
{
	use_data()->exstat = exstat;
}

void	get_exstat(int status)
{
	if (WIFEXITED(status))
		use_data()->exstat = WEXITSTATUS(status);
	else
		if (WIFSIGNALED(status))
			use_data()->exstat = WTERMSIG(status) + 128;
}

int	get_pid_status(void)
{
	int	status;

	waitpid(use_data()->pid, &status, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
	get_exstat(status);
	return (use_data()->exstat);
}
