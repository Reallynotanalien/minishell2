
#include "../../../includes/minishell.h"
#include "../../../includes/parsing.h"

//v check if it exists; if not, print error. Otherwise, check for rights; if invalid, print error.
//If all is valid, add the file in the right field of "cmd". (will be redirected at exec)
// >
int	token_redirout(t_token *token)
{
	int		fd;
	char	*token_lower;
	char	*token_copy;

	token_lower = ft_strlower(token->token);
	token_copy = ft_substr(token->token, 2, ft_strlen(token->token));
	token_copy = ft_strtrim_whitespaces(token_copy);
	if (access(token_copy, F_OK) == 0 
		|| access(token_lower, F_OK) == 0)
	{
		if (access (token_copy, W_OK) == 0
			|| access ((token_lower), W_OK) == 0)
			fd = open(token_copy, O_TRUNC | O_WRONLY);
		else
			return (free(token_lower), free(token_copy), -1);
	}
	else
		fd = open(token_copy, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (use_data()->outfile != STDOUT_FILENO)
		close(use_data()->outfile);
	use_data()->outfile = fd;
	return (free(token_lower), free(token_copy), 0);
}

int	token_redirappend(t_token *token)
{
	int		fd;
	char	*token_lower;
	char	*token_copy;

	token_lower = ft_strlower(token->token);
	token_copy = ft_substr(token->token, 3, ft_strlen(token->token));
	token_copy = ft_strtrim_whitespaces(token_copy);
	if (access(token_copy, F_OK) == 0 
		|| access(token_lower, F_OK) == 0)
	{
		if (access (token_copy, W_OK) == 0
			|| access ((token_lower), W_OK) == 0)
			fd = open(token_copy, O_APPEND | O_WRONLY);
		else
			return (free(token_lower), free(token_copy), -1);
	}
	else
		fd = open(token_copy, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (use_data()->outfile != STDOUT_FILENO)
		close(use_data()->outfile);
	printf("fd is: %i\n", fd);
	use_data()->outfile = fd;
	return (free(token_lower), free(token_copy), 0);
}

//<
int	token_redirin(t_token *token)
{
	int		fd;
	char	*token_lower;
	char	*token_copy;

	token_lower = ft_strlower(token->token);
	token_copy = ft_substr(token->token, 2, ft_strlen(token->token));
	token_copy = ft_strtrim_whitespaces(token_copy);
	if (access(token_copy, O_WRONLY == 0))
		fd = open(token_copy, O_WRONLY);
	else if (access(token_lower, O_WRONLY == 0))
		fd = open(token_lower, O_WRONLY);
	else
		return (free(token_lower), free(token_copy), ERROR);
	if (use_data()->infile != STDOUT_FILENO)
		close(use_data()->infile);
	use_data()->infile = fd;
	return (free(token_lower), free(token_copy), EXIT_SUCCESS);
}
