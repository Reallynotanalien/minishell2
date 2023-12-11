# include "../includes/minishell.h"

void	init_data(t_data *data)
{
	data->token = NULL;
	data->cmd = NULL;
	data->error_source = NULL;
	data->error_flag = 0;
	data->heredoc_flag = 0;
	data->exstat = 0;
	data->infile = STDIN_FILENO;
	data->outfile = STDOUT_FILENO;
	data->pid = 0;
	data->child = NO;
	data->new_env = NULL;
	data->line = NULL;
	data->line_cpy = NULL;
}
