/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:26:58 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/09 17:51:19 by edufour          ###   ########.fr       */
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

int	*get_pid_status(void)
{
	int	*status;

	status = ft_calloc(1, sizeof(int));
	waitpid(use_data()->pid, status, 0);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (status);
}
