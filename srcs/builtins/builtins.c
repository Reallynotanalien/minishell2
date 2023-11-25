#include "../../includes/minishell.h"

//print the args on STDOUT_FILENO
int	echo_builtin(char	**cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (cmd[1] && ft_strcmp(cmd[1], "-n"))
		ft_putchar_fd('\n', STDIN_FILENO);
	return (0);
}

//changes current working directory (env ? check allowed functions !)
int	cd_builtin(char **cmd)
{
	if (!cmd[1] || cmd[2])
		tmp_error("error with cd; too many or too few args\n");
	if (!chdir(cmd[1]))
		perror("ERROR : ");
	return (0);
}

// print current working directory on STDOUT_FILENO
int	pwd_builtin(char **cmd)
{
	char	*cwd;

	if (cmd[1])
		tmp_error("too many args for pwd\n");
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free (cwd);
	return (0);
}

//unsets an environment variable
//it follows the same rules as naming a variable (alnum, _, no digit first)
/*	1 : check if name is ok
	2 : allocate new env with -1 n_lines
	3 : if (new_env[i] != variable), keep in new_env*/
int	unset_builtin(char **cmd)
{
	int		i;
	int		i_update;
	char	**updated_env;
	char	*tmp;

	i = 0;
	while (cmd[++i])
		if (isvalid_varname(cmd[i]))
			return (tmp_error("invalid identifier in unset builtin"), 1);
	updated_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (use_data()->new_env[i])
	{
		tmp = get_varname(use_data()->new_env[i]);
		if (ft_strcmp(tmp, cmd[i]))
			updated_env[i_update++] = use_data()->new_env[i++];
		else
			i++;
		free (tmp);
	}
	free (use_data()->new_env);
	use_data()->new_env = updated_env;
	return (0);
}

//prints env
// int	env_builtin()
// {

// }

//gracefully exits minishell (the numeric value given as argument will be the exit code)
int	exit_builtin(char **cmd)
{
	int	i;

	i = -1;
	if (cmd[2])
		return (tmp_error("minishell: exit: too many arguments\n"), 1);
	if (cmd[1])
	{
		while (cmd[1][++i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				tmp_error("minishell: exit: a: numeric argument required\n");
				return (exit_program(ft_atoi(cmd[1])), 0);
			}
		}
		return (exit_program(ft_atoi(cmd[1])), 0);
	}
	return (exit_program(ft_atoi(cmd[1])), 0);
}

