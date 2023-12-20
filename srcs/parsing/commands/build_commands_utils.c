# include "../../../includes/minishell.h"

/*Uses get_next_line to take input from the terminal and put it in the
temporary file. If CTRL+C is pressed, the child is closed so that 
get_next_line will not be waiting for input.*/
void	heredoc_input(int temp_file, char *token)
{
	signal(SIGINT, heredoc_handler);
	while (get_next_line(0, &use_data()->here_doc_str))
	{
		if ((ft_strlen(use_data()->here_doc_str) == ft_strlen(token) + 1)
			&& (ft_strncmp(use_data()->here_doc_str, token,
					ft_strlen(token)) == 0))
		{
			free(use_data()->here_doc_str);
			break ;
		}
		else
			write(temp_file, use_data()->here_doc_str,
				ft_strlen(use_data()->here_doc_str));
		free(use_data()->here_doc_str);
	}
	exit (0);
}

/*Opens a temporary file called .here_doc and uses get_next_line to take input
from the terminal and put it in that file. It is then closed, then reopened
in RD_ONLY mode to use as input for the program. The output file is opened
with O_APPEND to deal with <<.*/
int	open_heredoc(t_token *tokens)
{
	int		here_doc;
	int		temp_file;
	int		*status;
	char	*token;

	signal(SIGINT, child_handler);
	temp_file = open(".here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (!temp_file)
		heredoc_error(HD_OPEN_ERROR, 1);
	token = ft_strtrim_whitespaces(ft_substr(tokens->token, 2,
				ft_strlen(tokens->token) - 2));
	use_data()->pid = fork();
	if (use_data()->pid == -1)
		heredoc_error(HD_FORK_ERROR, 1);
	else if (use_data()->pid == 0)
		heredoc_input(temp_file, token);
	status = get_pid_status();
	if (*status != 0)
		use_data()->error_flag = ERROR;
	close(temp_file);
	here_doc = open(".here_doc", O_RDONLY);
	use_data()->heredoc_flag = YES;
	free(token);
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
