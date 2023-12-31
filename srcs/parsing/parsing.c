/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:33:52 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/05 19:33:53 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//returns an allocated copy of the environment
// char	**copy_env(char **env)
// {
// 	char	**new_env;
// 	int		nb_lines;
// 	int		i;

// 	nb_lines = 0;
// 	while (env[nb_lines])
// 		nb_lines++;
// 	new_env = ft_calloc(nb_lines + 1, sizeof(char *));
// 	i = -1;
// 	while (env[++i])
// 		new_env[i] = ft_strdup(env[i]);
// 	return (new_env);
// }

/*Checks if the minishell args are valid and makes a copy
of the env variable to be used later.*/
// int	main_parsing(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	// if (argc != 1)
// 	// 	return (print_error(ARGC_ERROR));
// 	use_data()->new_env = copy_env(env);
// 	// if (!use_data()->new_env)
// 		// return (print_error(ENV_ERROR));
// 	// if (!argv)
// 	// 	return (print_error(ARGV_ERROR));
// 	return (0);
// }

/*First checks if all the quotes are closed, if not, returns ERROR
and sets the error flag to ERROR.
Then, removes all of the superfluous spaces in between words (except
for what's in between quotes), returns ERROR if something goes wrong
and sets the error flag to ERROR.
Then substitutes all of the environment variables it finds in the 
command line and stores it in a copy of the original line.
After all of that is done, splits the line into tokens. If something
goes wrong, the tokens are freed as well as the copy of the line.
Those tokens are then used to create a command list, in which each 
command will be associated with the right input and output file for
easy execution.*/

char	*remove_nonascii(char *str)
{
	char	*new_str;
	int		i;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] < 0 || str[i] > 127)
			new_str[i] = '?';
		else
			new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

void	line_parsing(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (use_data()->line[i]
		&& (use_data()->line[i] == ' ' || use_data()->line[i] == '\t'))
		i++;
	tmp = remove_nonascii(use_data()->line);
	free (use_data()->line);
	use_data()->line = tmp;
	if (i == (int)ft_strlen(use_data()->line)
		|| parse_quotes(use_data()->line) == ERROR
		|| remove_spaces(use_data()->line) == ERROR)
	{
		use_data()->error_flag = ERROR;
		return ;
	}
	do_substitutions(use_data()->line_cpy);
	if (split_tokens() == ERROR)
	{
		use_data()->error_flag = ERROR;
		return (free_tokens_if_not_empty());
	}
	build_commands();
	free_tokens_if_not_empty();
}
