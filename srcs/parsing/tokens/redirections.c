/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:56:16 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/10 13:23:52 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*copy_token(char *token, int type)
{
	if (token[type] && ft_iswhitespace(token[type]))
		return (ft_strtrim_whitespaces(ft_substr(token, type + 1,
					ft_strlen(token))));
	else
		return (ft_strtrim_whitespaces(ft_substr(token, type,
					ft_strlen(token))));
}

//Checks and handles potential errors, or redirects input/output.
int	token_redirout(t_token *token)
{
	int		fd;
	char	*t_lower;
	char	*t_copy;

	t_copy = copy_token(token->token, 1);
	t_lower = ft_strlower(t_copy);
	if (access(t_copy, F_OK) == 0 || access(t_lower, F_OK) == 0)
	{
		if (access (t_copy, W_OK) == 0 || access ((t_lower), W_OK) == 0)
			fd = open(t_copy, O_TRUNC | O_WRONLY);
		else
			return (free(t_lower), ft_printf(2, "minishell: %s: ", t_copy),
				free(t_copy), perror(NULL), set_exstat(NULL, 1), -1);
	}
	else
		fd = open(t_copy, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (free(t_lower), free(t_copy), set_exstat(NULL, 1),
			ft_printf(2, "minishell: %s: ", t_copy), perror(NULL), -1);
	if (use_data()->outfile != STDOUT_FILENO)
		close(use_data()->outfile);
	use_data()->outfile = fd;
	return (free(t_lower), free(t_copy), 0);
}

int	token_redirappend(t_token *token)
{
	int		fd;
	char	*t_lower;
	char	*t_copy;

	t_copy = copy_token(token->token, 2);
	t_lower = ft_strlower(t_copy);
	if (access(t_copy, F_OK) == 0 
		|| access(t_lower, F_OK) == 0)
	{
		if (access (t_copy, W_OK) == 0
			|| access ((t_lower), W_OK) == 0)
			fd = open(t_copy, O_APPEND | O_WRONLY);
		else
			return (free(t_lower), ft_printf(2, "minishell: %s: ", t_copy),
				free(t_copy), perror(NULL), set_exstat(NULL, 1), -1);
	}
	else
		fd = open(t_copy, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (use_data()->outfile != STDOUT_FILENO)
		close(use_data()->outfile);
	use_data()->outfile = fd;
	return (free(t_lower), free(t_copy), 0);
}

//<
int	token_redirin(t_token *token)
{
	int		fd;
	char	*t_lower;
	char	*t_copy;

	t_copy = copy_token(token->token, 1);
	t_lower = ft_strlower(t_copy);
	if (access(t_copy, F_OK | R_OK) == -1
		&& access(t_lower, F_OK | R_OK) == -1)
		return (free(t_lower), ft_printf(2, "minishell: %s: ", t_copy),
			free(t_copy), perror(NULL), set_exstat(NULL, 1), -1);
	fd = open(t_copy, O_RDONLY);
	if (fd < 0)
	{
		fd = open(t_lower, O_RDONLY);
		if (fd < 0)
			return (free(t_lower), free(t_copy),
				ft_printf(2, "minishell: %s: ", t_copy), perror(NULL),
				set_exstat(NULL, 1), -1);
	}
	if (use_data()->infile != STDIN_FILENO)
		close(use_data()->infile);
	use_data()->infile = fd;
	return (free(t_lower), free(t_copy), EXIT_SUCCESS);
}
