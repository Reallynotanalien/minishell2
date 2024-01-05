#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	use_data()->new_env = copy_env(env);
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
		clean_cmds();
		free (use_data()->line_cpy);
		use_data()->line_cpy = NULL;
		if (use_data()->heredoc_flag == YES)
			unlink(".here_doc");
	}
	return (0);
}
