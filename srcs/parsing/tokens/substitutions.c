/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:05:44 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 13:09:32 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//returns 1 if the character is an environment variable name delimiter.
int	is_delimiter(char c)
{
	if (!c || c == ' ' || c == '\t' || c == '\''
		|| c == '\"' || c == '$' || c == '<' || c == '>' || c == '|'
		|| c == '?' || c == ':')
		return (1);
	return (0);
}

/*Substitutes the variable which's symbol ($) is at 'index'
and places it in blocks[i_block].
Returns the len of the variable's name.
*/
int	substitute_block(char *line, int index, char **blocks, int i_block)
{
	int		i;
	char	*new_block;
	char	*var_name;
	char	*tmp;

	if (!line[index + 1])
		return (blocks[i_block] = ft_strdup("$"), 1);
	if (line[index + 1] == '$')
		return (blocks[i_block] = ft_strdup("$"), 2);
	i = index + 1;
	if (line[i] == '?')
		return (blocks[i_block] = ft_itoa(use_data()->exstat), 2);
	if (is_delimiter(line[i]) && line[i] != '$')
		return (blocks[i_block] = ft_strdup("$"), 1);
	while (!is_delimiter(line[i]))
		i++;
	var_name = ft_substr(line, index + 1, i - index - 1);
	tmp = ft_getenv(var_name);
	new_block = ft_strdup(tmp);
	if (!new_block)
	{
		blocks[i_block] = ft_calloc(1, 1);
		if (line[i] == ' ')
			i++;
	}
	else
		blocks[i_block] = new_block;
	return (free (tmp), free (var_name), i - index);
}

/*Separates the segments (blocks) into different arrays, 
finding and handling the variable names.*/
void	create_blocks(char *line, char **blocks)
{
	int	i;
	int	i_block;
	int	len;

	i = 0;
	i_block = 0;
	while (line[i])
	{
		len = 0;
		while (line[i + len] && !(line[i + len] == '$'
				&& !single_quoted(line, i + len)))
			len ++;
		if (line[i] != '$')
			blocks[i_block++] = ft_substr(line, i, len);
		i += len;
		if (line[i])
		{
			i += substitute_block(line, i, blocks, i_block);
			i_block++;
		}
	}
}

//Counts the number of segments (blocks) to allocate sufficient memory.
int	count_nbblocks(char *line)
{
	int	i;
	int	nb_blocks;
	int	flag_var;

	i = -1;
	flag_var = 0;
	nb_blocks = 1;
	while (line[++(i)])
	{
		if (line[i] == '$' && !single_quoted(line, i))
			nb_blocks += skip_envvar(line, &i, &flag_var);
		if (!line[i])
			return (nb_blocks);
		if ((flag_var == 1 && is_delimiter(line[i]))
			&& (line[i] != '?' || (line[(i) + 1] && line[(i) + 1] != '$')))
		{
			flag_var = 0;
			nb_blocks++;
		}
	}
	return (nb_blocks);
}

/*Handles all substitutions in readline's return. ($VAR, $?)
First counts the segments (Variable name VS strings), then
builds an array of arrays for the segments, 
replacing the variable names by their value before building the new string
from the concatenation of the segments.
*/
void	do_substitutions(char *line)
{
	int		nb_blocks;
	char	**blocks;
	char	*new_line;
	char	*tmp;
	int		i;

	nb_blocks = count_nbblocks(line);
	blocks = ft_calloc(nb_blocks + 1, sizeof(char *));
	create_blocks(line, blocks);
	new_line = ft_strdup(blocks[0]);
	i = 1;
	while (i < nb_blocks)
	{
		tmp = new_line;
		if (blocks[i] && blocks[i][0])
		{
			new_line = ft_strjoin(tmp, blocks[i]);
			free (tmp);
		}
		i++;
	}
	free_array(blocks);
	safe_free ((void **)&line);
	use_data()->line_cpy = new_line;
}
