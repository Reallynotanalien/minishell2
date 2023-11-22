# include "../../../includes/minishell.h"

t_token	*command_loop(t_token *tokens, char **command)
{
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			break ;
		else if (tokens->type == T_HEREDOC)
			use_data()->infile = open_heredoc(tokens);
		else if (tokens->type == T_INFILE)
			printf("token_redirin(tokens);\n");
		else if (tokens->type == T_OUTFILE)
			token_redirout(tokens);
		else if (tokens->type == T_APPEND)
			token_redirappend(tokens);
		else if (tokens->type == T_STR)
		{
			*command = join_free(*command, " ");
			*command = join_free(*command, tokens->token);
		}
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
