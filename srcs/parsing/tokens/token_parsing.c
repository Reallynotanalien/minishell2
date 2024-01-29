/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:33:09 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 16:04:13 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	parse_pipe(char *line, int index)
{
	if (index == 0)
		return (ft_printf(2, INV_TOKEN" '|'\n"), 1);
	if (!line[index + 1])
		return (ft_printf(2, INV_TOKEN" 'newline'\n"), 1);
	if (line[index + 1] == ' ' || line[index + 1] == '\t')
		index++;
	index++;
	if (line[index] == '|')
		return (ft_printf(2, INV_TOKEN" '|'\n"), 1);
	return (0);
}

int	parse_in_out(char *line, int index)
{
	if (!line[index])
		return (ft_printf(2, INV_TOKEN" 'newline'\n"), 1);
	if (is_redirection(line[index]))
	{
		if (line[index] == line[index + 1])
		{
			ft_printf(2, INV_TOKEN" '%c%c'\n",
				use_data()->line_cpy[index], use_data()->line_cpy[index]);
			return (1);
		}
		else
		{
			ft_printf(2, INV_TOKEN" '%c'\n",
				line[index]);
			return (1);
		}
	}
	return (0);
}

int	parsing_redirection(char *line, int index)
{
	if (!is_redirection(line[index])
		|| double_quoted(line, index) || single_quoted(line, index))
		return (0);
	if (line[index] == '|')
	{
		if (parse_pipe(line, index))
			return (set_exstat(258), ERROR);
	}
	else
	{
		if (line[index] == line[index + 1])
			index++;
		if (line[index + 1] == ' ' || line[index + 1] == '\t')
			index ++;
		index++;
		if (parse_in_out(line, index))
			return (set_exstat(258), ERROR);
	}
	return (0);
}
