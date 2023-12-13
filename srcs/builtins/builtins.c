#include "../../includes/minishell.h"

//print the args on STDOUT_FILENO
int	echo_builtin(char	**cmd)
{
	int	i_cmd;
	int	i_line;

	if (!cmd[1])
		ft_putchar_fd('\n', STDOUT_FILENO);
	i_cmd = 1;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		i_cmd++;
	while (cmd[i_cmd])
	{
		if (!cmd[i_cmd][0])
			i_cmd++;
		i_line = -1;
		while (cmd[i_cmd][++i_line])
		{
			if (double_quoted(cmd[i_cmd], i_line) 
				|| single_quoted(cmd[i_cmd], i_line)
				|| (cmd[i_cmd][i_line] != '\"' && cmd[i_cmd][i_line] != '\''))
				ft_putchar_fd(cmd[i_cmd][i_line], STDOUT_FILENO);
		}
		i_cmd++;
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (cmd[1] && ft_strcmp(cmd[1], "-n"))
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

//changes current working directory
int	cd_builtin(char **cmd)
{
	char	*tmp;

	if (!cmd[1])
	{
		tmp = ft_getenv("HOME");
		if (chdir("/Users/edufour"))
		{
			printf("minishell: cd: HOME not set\n");
			return (free (tmp), 1);
		}
		free (tmp);
	}
	else if (chdir(cmd[1]) == -1)
	{
		perror("minishell: cd: ");
		return (1);
	}
	return (0);
}

// print current working directory on STDOUT_FILENO
int	pwd_builtin(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free (cwd);
	return (0);
}

//when name is equal, set to null. then, until !new_env[i], new_env = new_env[i + 1];
int	unset_var(char *variable)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!isvalid_varname(variable))
	{
		printf("minishell: unset: \'%s\': not a valid identifier\n", variable);
		return (1);
	}
	i = -1;
	while (use_data()->new_env[++i])
	{
		tmp = get_varname(use_data()->new_env[i]);
		if (!ft_strcmp(tmp, variable))
		{
			free(tmp);
			break ;
		}
		free (tmp);
	}
	if (!use_data()->new_env[i])
		return (0);
	while (use_data()->new_env[i])
	{
		free (use_data()->new_env[i]);
		while (use_data()->new_env[i])
		{
			use_data()->new_env[i] = use_data()->new_env[i + 1];
			i++;
		}
	}
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

	i = 0;
	while (cmd[++i])
		unset_var(cmd[i]);
	return (0);
}

//prints env
int	env_builtin(void)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!use_data()->new_env || !use_data()->new_env[0])
	{
		printf("\n");
		return (0);
	}
	tmp = get_varvalue(use_data()->new_env[0]);
	while (use_data()->new_env[i])
	{
		if (tmp)
			printf("%s\n", use_data()->new_env[i]);
		free (tmp);
		tmp = get_varvalue(use_data()->new_env[++i]);
	}
	free(tmp);
	return (0);
}

//gracefully exits minishell (the numeric value given as argument will be the exit code)
int	exit_builtin(char **cmd)
{
	int	i;

	i = -1;
	if (cmd[1] && cmd[2])
		return (print_error("minishell: exit: too many arguments"), 1);
	if (cmd[1])
	{
		while (cmd[1][++i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				printf("minishell: exit: %s: numeric argument required\n", 
					cmd[1]);
				printf("exit\n");
				return (exit_program(255), 0);
			}
		}
		printf("exit\n");
		return (exit_program(ft_atoi(cmd[1])), 0);
	}
	printf("exit\n");
	return (exit_program(0), 0);
}
