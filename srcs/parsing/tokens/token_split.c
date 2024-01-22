/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:26:22 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/22 16:53:08 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	iterate_until_space(char *line, int *end)
{
	while (line[*end] && line[*end] != ' ' && line[*end] != '\t'
		&& !(is_redirection(line[*end])
			&& !double_quoted(line, *end) && !single_quoted(line, *end)))
		(*end)++;
	if (is_redirection(line[*end]))
		(*end)--;
}

void	skip_str(int *end)
{
	while (use_data()->line_cpy[*end]
		&& !(is_redirection(use_data()->line_cpy[*end])
			&& !double_quoted(use_data()->line_cpy, *end)
			&& !single_quoted(use_data()->line_cpy, *end)))
		(*end)++;
	if (is_redirection(use_data()->line_cpy[*end]))
		(*end)--;
}

void	skip_redirection(int *end)
{
	if ((use_data()->line_cpy[*end] == '>'
			&& use_data()->line_cpy[(*end) + 1] == '>')
		|| (use_data()->line_cpy[*end] == '<'
			&& use_data()->line_cpy[(*end) + 1] == '<'))
		(*end) += 2;
	if (use_data()->line_cpy[(*end) + 1] == ' '
		|| use_data()->line_cpy[(*end) + 1] == '\t')
		(*end)++;
	(*end)++;
	iterate_until_space(use_data()->line_cpy, end);
	if (is_redirection(use_data()->line_cpy[*end]))
		(*end)--;
}

int	loop(int start, int *end)
{
	if (start != 0)
	{
		start++;
		(*end)++;
	}
	if (!use_data()->line_cpy[*end])
		return (0);
	if (use_data()->line_cpy[*end] == '|'
		&& (use_data()->line_cpy[(*end) + 1] == ' '
			|| use_data()->line_cpy[(*end) + 1] == '\t'))
		(*end)++;
	else if (use_data()->line_cpy[*end] == '>'
		|| use_data()->line_cpy[*end] == '<')
		skip_redirection(end);
	else if (use_data()->line_cpy[*end] != '|')
		skip_str(end);
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
	while (use_data()->line_cpy[*end])
	{
		if (loop(*end, end))
			return (free(end), ERROR);
	}
	return (free(end), 0);
}
