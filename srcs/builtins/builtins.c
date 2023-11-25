#include "../../includes/minishell.h"

//print the args on STDOUT_FILENO
int	echo_builtin(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[++i])
	{
		ft_putstr_fd(cmd->cmd[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n"))
		ft_putchar_fd('\n', STDIN_FILENO);
	return (0);
}

//changes current working directory (env ? check allowed functions !)
int	cd_builtin(t_command *cmd)
{
	if (!cmd->cmd[1] || cmd->cmd[2])
		tmp_error("error with cd; too many or too few args\n");
	if (!chdir(cmd->cmd[1]))
		perror("ERROR : ");
	return (0);
}

// print current working directory on STDOUT_FILENO
int	pwd_builtin(t_command *cmd)
{
	char	*cwd;

	if (cmd->cmd[1])
		tmp_error("too many args for pwd\n");
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free (cwd);
	return (0);
}

//unsets an environment variable
int unset_builtin()
{

}

//prints env
int	env_builtin()
{

}

//gracefully exits minishell (the numeric value given as argument will be the exit code)
int exit_builtin(t_command *cmd)
{
	if (cmd->cmd[1])
	{
		if (!ft_isdigit(cmd->cmd[1]))
			tmp_error("minishell: exit: a: numeric argument required\n");
		else
			exit_program(ft_atoi(cmd->cmd[1]));
	}
	if (cmd->cmd[2])
		tmp_error("minishell: exit: too many arguments\n");
}

