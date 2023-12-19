# include "../../../includes/minishell.h"

/*Opens a temporary file called .here_doc and uses get_next_line to take input
from the terminal and put it in that file. It is then closed, then reopened
in RD_ONLY mode to use as input for the program. The output file is opened
with O_APPEND to deal with << >>.*/
int	open_heredoc(t_token *tokens)
{
	int		here_doc;
	int		*status;

	use_data()->temp_file = open(".here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0644);
	use_data()->here_doc_token = ft_strtrim_whitespaces(ft_substr(tokens->token, 2, ft_strlen(tokens->token) - 2));
	if (tokens->next && tokens->next->type == T_STR)
		printf("Heredoc should not work here because there is something else than a redirection after the EOF\n");
	use_data()->pid = fork();
	if (use_data()->pid == -1)
		printf("FORK DID NOT WORK\n");
	else if (use_data()->pid == 0)
	{
		signal(SIGINT, heredoc_handler);
		while (get_next_line(0, &use_data()->here_doc_str))
		{
			if ((ft_strlen(use_data()->here_doc_str) == ft_strlen(use_data()->here_doc_token) + 1)
				&& (ft_strncmp(use_data()->here_doc_str, use_data()->here_doc_token, ft_strlen(use_data()->here_doc_token)) == 0))
			{
				free(use_data()->here_doc_str);
				break ;
			}
			else
				write(use_data()->temp_file, use_data()->here_doc_str, ft_strlen(use_data()->here_doc_str));
			free(use_data()->here_doc_str);
		}
		if (use_data()->here_doc_str == NULL)
			printf("ctrl+d was pushed\n");
		exit (0);
	}
	status = ft_calloc(1, sizeof(int));
	waitpid(use_data()->pid, status, 0);
	if (*status == 0)
		ft_printf(2, "exited normally\n");
	else
		ft_printf(2, "exited abnormally\n");
	close(use_data()->temp_file);
	here_doc = open(".here_doc", O_RDONLY);
	use_data()->heredoc_flag = YES;
	free(use_data()->here_doc_token);
	signal(SIGINT, interruption_handler);
	return (here_doc);
}

int	contains_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_iswhitespace(str[i]))
			return (YES);
		i++;
	}
	return (NO);
}
