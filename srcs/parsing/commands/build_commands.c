# include "../../../includes/minishell.h"

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
	}
	i_add = -1;
	while (add[++i_add])
		new_str[i + i_add] = add[i_add];
	new_str[i + i_add] = '\0';
	if (str)
		free (str);
	return (new_str);
}


t_token	*command_loop(t_token *tokens, char **command)
{
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			break ;
		else if (tokens->type == T_HEREDOC)
			use_data()->infile = open_heredoc(tokens);
		else if (tokens->type == T_INFILE)
			token_redirin(tokens);
		else if (tokens->type == T_OUTFILE)
			token_redirout(tokens);
		else if (tokens->type == T_APPEND)
			token_redirappend(tokens);
		else if (tokens->type == T_STR)
			*command = join_command(*command, tokens->token);
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
	}
	return (tokens);
}

void	build_commands(void)
{
	t_token	*tokens;
	char	*command;
	int		i;

	i = 1;
	tokens = use_data()->token;
	while (tokens)
	{
		command = NULL;
		use_data()->infile = STDIN_FILENO;
		use_data()->outfile = STDOUT_FILENO;
		tokens = command_loop(tokens, &command);
		add_command(command, use_data()->infile, use_data()->outfile);
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
	}
}
