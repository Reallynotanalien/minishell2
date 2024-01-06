/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:27:47 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/05 20:27:49 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	parse_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (double_quoted(str, i) == -1 || single_quoted(str, i) == -1)
			return (ft_printf(2, "minishell: quotations are not closed\n"),
				set_exstat(NULL, 1), ERROR);
	}
	if (double_quoted(str, i) == -1 || single_quoted(str, i) == -1)
		return (ft_printf(2, "minishell: quotations are not closed\n"),
			set_exstat(NULL, 1), ERROR);
	return (0);
}

int	find_lenght(char *str, int end)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < end && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (i < end)
	{
		while (i < end && ((str[i] != ' ' && str[i] != '\t')
				|| (double_quoted(str, i) || single_quoted(str, i))))
		{
			i++;
			len++;
		}
		if (i < end)
			len++;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
	}
	return (len);
}

char	*skip_consecutives(char *str, int i, int end)
{
	int		i_new;
	char	*new_str;

	new_str = ft_calloc(find_lenght(str, end) + 1, sizeof(char));
	if (!new_str)
		return (ft_printf(2, "minishell: fatal error\n"),
			set_exstat(NULL, 1), NULL);
	i_new = 0;
	while (i < end)
	{
		while (str[i] && ((str[i] != ' ' && str[i] != '\t')
				|| (double_quoted(str, i) || single_quoted(str, i))))
			new_str[i_new++] = str[i++];
		if (i < end)
			new_str[i_new++] = ' ';
		while (str[i] == ' ' || str[i] == '\t')
			i++;
	}
	return (new_str);
}

int	remove_spaces(char *str)
{
	int		i;
	int		end;
	char	*tmp;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	end = ft_strlen(str) - 1;
	while (str[end] == ' ' || str[end] == '\t')
		end--;
	if (end != i)
		end++;
	if (end == i)
	{
		use_data()->line_cpy = ft_strdup(str);
		return (0);
	}
	else
	{
		tmp = skip_consecutives(str, i, end);
		use_data()->line_cpy = tmp;
	}
	if (use_data()->line_cpy == NULL)
		return (ERROR);
	return (0);
}
