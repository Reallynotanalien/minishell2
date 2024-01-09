/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:53:55 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/05 19:53:57 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_cmds(void)
{
	t_command	*tmp;

	while (use_data()->cmd)
	{
		tmp = use_data()->cmd->next;
		free_array(use_data()->cmd->cmd);
		safe_free ((void **)&(use_data()->cmd->path));
		safe_free((void **)&(use_data()->cmd->lower_cmd));
		safe_free((void **)&(use_data()->cmd));
		use_data()->cmd = tmp;
	}
}

void	clean_tokens(void)
{
	t_token	*tmp;

	while (use_data()->token)
	{
		tmp = use_data()->token->next;
		safe_free ((void **)&use_data()->token->token);
		safe_free ((void **)&use_data()->token);
		use_data()->token = tmp;
	}
}

void	clean_after_loop(void)
{
	safe_free((void **)&(use_data()->line));
	safe_free((void **)&(use_data()->line_cpy));
	clean_tokens();
	clean_cmds();
	if (use_data()->heredoc_flag == YES)
		unlink(".here_doc");
}

void	exit_program(int code)
{
	t_data	*data;

	clean_after_loop();
	restore_attributes();
	rl_clear_history();
	free_array(use_data()->new_env);
	data = use_data();
	safe_free((void **)&data);
	exit(code);
}
