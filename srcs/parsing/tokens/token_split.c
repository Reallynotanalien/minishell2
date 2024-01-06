/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:26:22 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/05 20:26:24 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*Iterates until it finds another double quote character.*/
int	iterate_until_quotes_are_closed(char *line, int end)
{
	while (line[end + 1] && !is_double_quote(line[end + 1]))
		end++;
	if (line[end + 1] != ' ' && line[end + 1] != '\t')
		return (end);
	return (end + 1);
}

/*Iterates until a redirection character is found. If it finds a double
quote, iterates until it finds the closing quote so that we do not
include any redirection character that is contained between those quotes
into our count, since those will be part of the string.*/
int	iterate_until_redir(char *line, int end, int start)
{
	if (start == 0 && is_double_quote(use_data()->line_cpy[start]))
	{
		end = iterate_until_quotes_are_closed(use_data()->line_cpy, end + 1);
		end++;
	}
	while (line[end] && line[end + 1]
		&& !is_redirection(line[end + 1]))
	{
		if (line[end + 1] == '"')
			end = iterate_until_quotes_are_closed(line, end + 1);
		end++;
	}
	return (end);
}

int	iterate_until_space(char *line, int end)
{
	while (line[end] && line[end + 1]
		&& (line[end + 1] != ' ' && line[end + 1] != '\t'))
	{
		if (line[end + 1] == '"')
			end = iterate_until_quotes_are_closed(line, end + 1);
		end++;
	}
	return (end);
}

size_t	loop(size_t s)
{
	int	end;

	end = s;
	if (!is_redirection(use_data()->line_cpy[s]))
		end = iterate_until_redir(use_data()->line_cpy, end, s);
	else
	{
		if (parsing_redirection(use_data()->line_cpy, s) == ERROR)
			return (0);
		end++;
		if (use_data()->line_cpy[s] == '<'
			|| use_data()->line_cpy[s] == '>')
		{
			if (use_data()->line_cpy[s + 1] == '>'
				|| use_data()->line_cpy[s + 1] == '<')
				end++;
			if (use_data()->line_cpy[s + 1] == '<')
				end = iterate_until_redir(use_data()->line_cpy, end, end);
			else
				end = iterate_until_space(use_data()->line_cpy, end);
		}
	}
	new_token(s, end);
	s = end + 1;
	return (s);
}

/*Iterates through the line and splits it into a linked list of tokens.
Everytime there is a redirection, it gets splitted into it's own token
with all of the words that follows it, until the next redirection. 
If a redirection is found in between double quotes, it gets treated as part
of the string and not as a redirection.
Everytime there is a pipe, the pipe gets put into a token all alone.
All of the superfluous whitespaces that would be in between tokens are also
deleted.
This function works wether the strings and the redirections are separated by
a space or not. (Ex: cat | cat OR cat|cat both work.).*/
int	split_tokens(void)
{
	size_t	s;

	s = 0;
	while (s <= ft_strlen(use_data()->line_cpy) && use_data()->line_cpy[s])
	{
		s = loop(s);
		if (s == 0)
			return (ERROR);
	}
	return (0);
}
