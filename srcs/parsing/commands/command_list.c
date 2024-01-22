/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:27:55 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/22 16:43:30 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_words(char *str)
{
	int	i;
	int	nb_words;

	nb_words = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' '
			&& !double_quoted(str, i) && !single_quoted(str, i))
			nb_words++;
		i++;
	}
	return (nb_words);
}

char	*split_next_word(char *str, int *index)
{
	char	*new_word;
	int		len;

	len = 0;
	while (str[*index + len] && !(str[*index + len] == ' '
			&& !double_quoted(str, *index + len)
			&& !single_quoted(str, *index + len)))
		len++;
	if (len == 0)
		return (ft_calloc(1, 1));
	new_word = ft_calloc(len + 1, sizeof(char));
	len = 0;
	while (str[*index] && !(str[*index] == ' '
			&& !double_quoted(str, *index) && !single_quoted(str, *index)))
	{
		if (!is_quote(str[*index])
			|| double_quoted(str, *index) || single_quoted(str, *index))
			new_word[len++] = str[*index];
		(*index)++;
	}
	if (str[*index])
		(*index)++;
	return (new_word);
}

char	**ft_split_quotes(char *s)
{
	char	**new_array;
	int		nb_words;
	int		*i;

	nb_words = count_words(s);
	if (nb_words == 0)
		return (ft_calloc(1, sizeof(char *)));
	new_array = ft_calloc(nb_words + 1, sizeof(char *));
	i = ft_calloc(1, sizeof(int));
	nb_words = 0;
	*i = 0;
	while (s[*i])
		new_array[nb_words++] = split_next_word(s, i);
	free(i);
	free(s);
	return (new_array);
}

t_command	*skip_commands(t_command *new)
{
	t_command	*next;

	next = use_data()->cmd;
	while (next->next != NULL)
		next = next->next;
	next->next = new;
	return (next);
}

t_command	*add_command(char *command, int infile, int outfile)
{
	t_command	*new;

	new = create_command();
	if (!new)
		return (NULL);
	new->cmd = (char **)ft_split_quotes(command);
	new->lower_cmd = ft_strlower(new->cmd[0]);
	if (!confirm_builtin(new))
		get_path(new);
	new->infile = infile;
	new->outfile = outfile;
	if (use_data()->cmd == NULL)
		use_data()->cmd = new;
	else
		skip_commands(new);
	if (!new->cmd[0][0])
	{
		use_data()->error_flag = 1;
		ft_printf(2, "minishell: : command not found\n");
	}
	return (use_data()->cmd);
}
