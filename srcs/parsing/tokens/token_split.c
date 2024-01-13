/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:26:22 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/13 16:54:02 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//returns the index of the first found redirection, or end of str
int	iterate_until_redir(char *line, int start)
{
	int	*index;

	index = ft_calloc(1, sizeof(int));
	*index = start;
	if (start > 0)
		(*index)++;
	if (!line[*index])
		return (free(index), start);
	while (line[*index] && !(is_redirection(line[*index])
			&& !double_quoted(line, *index) && !single_quoted(line, *index)))
		(*index)++;
	start = *index;
	return (free(index), start);
}

void	iterate_until_space(char *line, int *end)
{
	while (line[*end] && line[*end] != ' ' && line[*end] != '\t'
		&& !(is_redirection(line[*end])
			&& !double_quoted(line, *end) && !single_quoted(line, *end)))
		(*end)++;
	if (is_redirection(line[*end]))
		(*end)--;
}

void	skip_redirection(int start, int *end)
{
	if ((use_data()->line_cpy[start] == '>'
			&& use_data()->line_cpy[start + 1] == '>')
		|| (use_data()->line_cpy[start] == '<'
			&& use_data()->line_cpy[start + 1] == '<'))
		(*end)++;
	(*end)++;
	if (use_data()->line_cpy[(*end) + 1] == ' ')
		(*end) += 2;
	(*end)++;
	iterate_until_space(use_data()->line_cpy, end);
}

int	loop(int start, int *end)
{
	if (start != 0)
		start++;
	if (!is_redirection(use_data()->line_cpy[start]))
	{
		*end = iterate_until_redir(use_data()->line_cpy, start);
		(*end)--;
	}
	else
	{
		if (parsing_redirection(use_data()->line_cpy, start) == ERROR)
			return (1);
		if (use_data()->line_cpy[start] == '|')
		{
			if (use_data()->line_cpy[start + 1] == ' ')
				(*end)++;
			(*end)++;
		}
		else
			skip_redirection(start, end);
	}
	new_token(start, (*end));
	if (*end == 0)
		(*end)++;
	return (0);
}

//*end will always be the last index of the previous token
int	split_tokens(void)
{
	int	*end;

	end = ft_calloc(1, sizeof(int));
	*end = 0;
	while (use_data()->line_cpy[*end]
		&& (use_data()->line_cpy[(*end) + 1] || *end == 0))
	{
		if (loop(*end, end))
			return (free(end), ERROR);
	}
	return (free(end), 0);
}
