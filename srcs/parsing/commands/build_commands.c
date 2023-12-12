# include "../../../includes/minishell.h"

//join add to str, adding a space between.
char	*join_command(char *str, char *add)
{
	char	*new_str;
	int		i;
	int		i_add;

	if (str == NULL)
		new_str = ft_calloc(ft_strlen(add) + 2, sizeof(char));
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
	return (new_str);
	if (str)
		free (str);
}

//needs to return the str containing everything but redirections and pipes
t_token	*command_loop(t_token *tokens)
{
	char	*command;

	printf("I got inside the command loop\n");
	command = NULL;
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
			command = join_command(command, tokens->token);
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
		printf("I got to the end of the command loop\n");
	}
	add_command(command, use_data()->infile, use_data()->outfile);
	return (tokens);
}

void	build_commands(void)
{
	t_token	*tokens;
	char	*command;

	tokens = use_data()->token;
	while (tokens)
	{
		command = NULL;
		use_data()->infile = STDIN_FILENO;
		use_data()->outfile = STDOUT_FILENO;
		tokens = command_loop(tokens);
		if (tokens->next)
			tokens = tokens->next;
		else
			break ;
	}
}
