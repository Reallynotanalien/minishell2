/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:53:13 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 11:35:19 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	if (!isatty(0))
		return (1);
	use_data()->new_env = copy_array(env);
	while (1)
	{
		signals();
		use_data()->line = readline("minishell$> ");
		use_data()->old_stdin = dup(STDIN_FILENO);
		use_data()->old_stdout = dup(STDOUT_FILENO);
		if (use_data()->line && *use_data()->line)
		{
			line_parsing();
			if (use_data()->error_flag != ERROR)
				exec(use_data()->cmd);
			use_data()->error_flag = 0;
			add_history(use_data()->line);
		}
		if (use_data()->line == NULL)
			exit_program(1);
		clean_after_loop();
	}
	return (0);
}
