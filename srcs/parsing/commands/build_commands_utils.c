/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:29:29 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/12 14:30:56 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	add_str(void)
{
	use_data()->here_doc_str = readline("> ");
	return (ft_strlen(use_data()->here_doc_str));
}

void	heredoc_input(int temp_file, char *token)
{
	signal(SIGINT, heredoc_handler);
	while (add_str())
	{
		if ((ft_strlen(use_data()->here_doc_str) == ft_strlen(token))
			&& (ft_strncmp(use_data()->here_doc_str, token,
					ft_strlen(token)) == 0))
		{
			ft_putchar_fd(EOF, temp_file);
			safe_free((void **)&(use_data()->here_doc_str));
			exit_program (0);
		}
		else
			write(temp_file, use_data()->here_doc_str,
				ft_strlen(use_data()->here_doc_str));
		safe_free((void **)&(use_data()->here_doc_str));
	}
	safe_free((void **)&token);
}

/*Opens a temporary file called .here_doc and uses get_next_line to take input
from the terminal and put it in that file. It is then closed, then reopened
in RD_ONLY mode to use as input for the program. The output file is opened
with O_APPEND to deal with << >>.*/
int	open_heredoc(t_token *tokens)
{
	int		here_doc;
	int		temp_file;
	int		*status;
	char	*token;

	signal(SIGINT, child_handler);
	temp_file = open(".here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (!temp_file)
		ft_printf(2, HD_OPEN_ERROR);
	token = ft_strtrim_whitespaces(ft_substr(tokens->token, 2,
				ft_strlen(tokens->token) - 2));
	use_data()->pid = fork();
	if (use_data()->pid == -1)
		ft_printf(2, HD_FORK_ERROR);
	else if (use_data()->pid == 0)
		heredoc_input(temp_file, token);
	safe_free((void **)&token);
	status = get_pid_status();
	if (*status != 0)
		use_data()->error_flag = ERROR;
	close(temp_file);
	here_doc = open(".here_doc", O_RDONLY);
	use_data()->heredoc_flag = YES;
	signal(SIGINT, interruption_handler);
	return (here_doc);
}

int	contains_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (YES);
		i++;
	}
	return (NO);
}

void	free_commands_if_not_empty(void)
{
	t_command	*temp;

	if (!use_data()->cmd)
		return ;
	while (use_data()->cmd)
	{
		temp = use_data()->cmd->next;
		free(use_data()->cmd);
		use_data()->cmd = temp;
	}
}

int	is_quote(char check)
{
	if (check == '\'' || check == '\"')
		return (1);
	return (0);
}
