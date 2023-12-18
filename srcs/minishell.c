#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	ft_printf(1, "hello this is from printf :) %s %d", "hi", 10);
	if (main_parsing(argc, argv, env) == ERROR)
		exit(1);
	signals(); 
	while (1)
	{
		use_data()->line = readline("minishell$> ");
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
		free(use_data()->line);
		free_commands_if_not_empty();
		if (use_data()->heredoc_flag == YES)
			unlink(".here_doc");
	}
	cleanup();
	return (0);
}
