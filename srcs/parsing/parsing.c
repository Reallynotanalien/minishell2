/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:33:52 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/16 15:04:00 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*First checks if all the quotes are closed, if not, returns ERROR
and sets the error flag to ERROR.
Then, removes all of the superfluous spaces in between words (except
for what's in between quotes), returns ERROR if something goes wrong
and sets the error flag to ERROR.
Then substitutes all of the environment variables it finds in the 
command line and stores it in a copy of the original line.
After all of that is done, splits the line into tokens. If something
goes wrong, the tokens are freed as well as the copy of the line.
Those tokens are then used to create a command list, in which each 
command will be associated with the right input and output file for
easy execution.*/

char	*remove_nonascii(char *str)
{
	char	*new_str;
	int		i;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] < 0 || str[i] > 127)
			new_str[i] = '?';
		else
			new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

int	ignore_tabs(int i)
{
	while (use_data()->line[i]
		&& (use_data()->line[i] == ' ' || use_data()->line[i] == '\t'))
		i++;
	return (i);
}

int	parse_redirections(void)
{
	int	i;

	i = 0;
	while (use_data()->line_cpy[i])
	{
		if (is_redirection(use_data()->line_cpy[i])
			&& !single_quoted(use_data()->line_cpy, i)
			&& !double_quoted(use_data()->line_cpy, i))
		{
			if (parsing_redirection(use_data()->line_cpy, i))
				return (1);
			else if (use_data()->line_cpy[i] == use_data()->line_cpy[i + 1])
				i++;
		}
		i++;
	}
	return (0);
}

void	line_parsing(void)
{
	int		i;

	i = ignore_tabs(0);
	if (i == (int)ft_strlen(use_data()->line)
		|| parse_quotes(use_data()->line) == ERROR
		|| remove_spaces(use_data()->line) == ERROR)
	{
		use_data()->error_flag = ERROR;
		return ;
	}
	do_substitutions(use_data()->line_cpy);
	if (parse_redirections() || split_tokens() == ERROR)
	{
		use_data()->error_flag = ERROR;
		return ;
	}
	if (build_commands())
		use_data()->error_flag = ERROR;
}

int	skip_envvar(char *line, int *i, int *flag_var)
{
	int	nb_blocks;

	nb_blocks = 0;
	if (*i != 0)
		nb_blocks++;
	(*flag_var) = 1;
	if (line[(*i) + 1] == '$')
		(*i)++;
	(*i)++;
	return (nb_blocks);
}
