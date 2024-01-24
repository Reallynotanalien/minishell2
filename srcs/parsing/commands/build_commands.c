/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:28:01 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/24 18:08:58 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//join add to str, adding a space between.
char	*join_command(char *str, char *add)
{
	char	*new_str;
	int		i;
	int		i_add;

	if (str == NULL)
		new_str = ft_calloc(ft_strlen(add) + 1, sizeof(char));
	else
		new_str = ft_calloc(ft_strlen(str) + ft_strlen(add) + 2, sizeof(char));
	i = 0;
	if (str)
	{
		i = -1;
		while (str[++i])
			new_str[i] = str[i];
		new_str[i] = ' ';
		i++;
	}
	i_add = -1;
	while (add[++i_add])
		new_str[i + i_add] = add[i_add];
	new_str[i + i_add] = '\0';
	if (str)
		safe_free((void **)&str);
	return (new_str);
}

//needs to return the str containing everything but redirections and pipes
int	command_loop(t_token **tokens)
{
	char	*command;

	command = NULL;
	while (*tokens)
	{
		if ((*tokens)->type == T_PIPE)
			break ;
		else if ((*tokens)->type == T_HEREDOC)
		{
			if (use_data()->infile != STDIN_FILENO)
				close (use_data()->infile);
			use_data()->infile = open_heredoc(*tokens, command);
		}
		else if (((*tokens)->type == T_INFILE && token_redirin(*tokens) == -1)
			|| ((*tokens)->type == T_OUTFILE && token_redirout(*tokens) == -1)
			|| ((*tokens)->type == T_APPEND
				&& token_redirappend(*tokens) == -1))
			return (1);
		else if ((*tokens)->type == T_STR)
			command = join_command(command, (*tokens)->token);
		if ((*tokens)->next)
			*tokens = (*tokens)->next;
		else
			break ;
	}
	if (command)
		add_command(command, use_data()->infile, use_data()->outfile);
	return (0);
}

int	build_commands(void)
{
	t_token	*tokens;

	tokens = use_data()->token;
	while (tokens)
	{
		use_data()->infile = STDIN_FILENO;
		use_data()->outfile = STDOUT_FILENO;
		if (command_loop(&tokens))
			return (1);
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
	}
	return (0);
}

t_command	*create_command(void)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}
