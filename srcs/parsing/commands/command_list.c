# include "../../../includes/minishell.h"

t_command	*create_command(void)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

int	is_quote(char check)
{
	if (check == '\'' || check == '\"')
		return (1);
	return (0);
}

int	count_words(char *str)
{
	int	i;
	int	nb_words;

	nb_words = 1;
	i = 0;
	nb_words = 0;
	while (str[i])
	{
		if (str[i] == ' '
			&& !double_quoted(str, i) && !single_quoted(str, i))
			nb_words++;
		i++;
	}
	return (nb_words);
}

//returns the next command's argument as a char *. Splits on spaces
//except if quoted, and returns an allocated empty char * if there is nothing. Removes unquoted quotes.
char *split_next_word(char *str, int *index)
{
	char	*new_word;
	int		len;

	len = 0;
	while (str[*index + len] && !(str[*index + len] == ' '
		&& !double_quoted(str, *index + len) && !single_quoted(str, *index + len)))
		len++;
	if (len == 0)
		return (ft_calloc(1, 1));
	new_word = ft_calloc(len + 1, sizeof(char));
	len = 0;
	while (str[*index] && !(str[*index] == ' ' && !double_quoted(str, *index) && !single_quoted(str, *index)))
	{
		if (!is_quote(str[*index])
			|| double_quoted(str, *index) || single_quoted(str, *index))
			new_word[len++] = str[*index];
		(*index)++;
	}
	if (str[*index])
		(*index)++;
	return (new_word);
	//need to make sure *index is ok
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
	return (new_array);
}

t_command	*add_command(char *command, int infile, int outfile)
{
	t_command	*new;
	t_command	*next;

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
	{
		next = use_data()->cmd;
		while (next->next != NULL)
			next = next->next;
		next->next = new;
	}
	if (!new->cmd[0][0])
	{
		use_data()->error_flag = 1;
		ft_printf(2, "minishell: : command not found\n");
	}
	return (use_data()->cmd);
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

void	view_commands(void)
{
	t_command	*cmd;
	int			i;
	int			j;

	i = 1;
	cmd = use_data()->cmd;
	while (cmd)
	{
		j = 0;
		printf("----------------\n");
		printf("command%d\n", i++);
		if (cmd->cmd == NULL)
			printf("NULL\n");
		else
		{
			while (cmd->cmd[j] != NULL)
			{
				printf("%d:[%s]\n", j, (char *)cmd->cmd[j]);
				j++;
			}
		}
		printf("infile no: %i\n", cmd->infile);
		printf("outfile no: %i\n", cmd->outfile);
		cmd = cmd->next;
	}
}
