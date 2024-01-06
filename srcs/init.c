/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:34:57 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/05 19:35:00 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_data *data)
{
	data->token = NULL;
	data->cmd = NULL;
	data->error_flag = 0;
	data->heredoc_flag = 0;
	data->exstat = 0;
	data->infile = STDIN_FILENO;
	data->outfile = STDOUT_FILENO;
	data->pid = 0;
	data->child = NO;
	data->new_env = NULL;
	data->line = NULL;
	data->line_cpy = NULL;
	data->old_stdin = 0;
	data->old_stdout = 0;
}
