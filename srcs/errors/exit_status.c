# include "../../includes/minishell.h"

int	*get_pid_status(void)
{
	int	*status;

	status = ft_calloc(1, sizeof(int));
	waitpid(use_data()->pid, status, 0);
	return (status);
}

