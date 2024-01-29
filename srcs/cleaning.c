/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:53:57 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 14:39:27 by edufour          ###   ########.fr       */
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
		if (use_data()->cmd->infile != STDIN_FILENO)
			close(use_data()->cmd->infile);
		if (use_data()->cmd->outfile != STDOUT_FILENO)
			close(use_data()->cmd->outfile);
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
	if (use_data()->old_stdin != 0)
		dup2(use_data()->old_stdin, STDIN_FILENO);
	if (use_data()->old_stdout != 0)
		dup2(use_data()->old_stdout, STDOUT_FILENO);
	if (use_data()->infile != STDIN_FILENO)
		close(use_data()->infile);
	if (use_data()->outfile != STDOUT_FILENO)
		close(use_data()->outfile);
	use_data()->infile = STDIN_FILENO;
	use_data()->outfile = STDOUT_FILENO;
	safe_close_file(use_data()->old_stdin);
	use_data()->old_stdin = 0;
	safe_close_file(use_data()->old_stdout);
	use_data()->old_stdout = 0;
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

void	clean_heredoc(char *string, char *token, char *cmd, int fd)
{
	close (fd);
	safe_free((void **)&string);
	safe_free((void **)&token);
	safe_free((void **)&cmd);
}
