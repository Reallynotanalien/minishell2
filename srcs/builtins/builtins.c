#include "../../includes/minishell.h"

//checks if the given string is a builtin name.

//returns buff, which will contain str in lowercase.
char	*ft_lowerbuiltin(char *str, char *buff)
{
	int		i;

	i = 0;
	ft_bzero(buff, ft_strlen(str) + 1);
	i = -1;
	while (str[++i])
		buff[i] = ft_tolower(str[i]);
	return (buff);
}

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

void	print_export(char *env_var)
{
	int	i;

	printf("declare -x ");
	i = -1;
	while (env_var && env_var[++i] != '=')
		printf("%c", env_var[i]);
	if (env_var[i] == '=')
	{
		printf("=\"");
		while (env_var[++i])
			printf(env_var[i]);
		printf("\"\n");
	}
}

char	*get_varname(char *variable)
{
	int		i;
	char	*var_name;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (variable[i] && variable[i] != '=')
	{
		var_name[i] = variable[i];
		i++;
	}
	return (var_name);
}

char	*get_varvalue(char *variable)
{
	int		i;
	int		i_value;
	char	*value;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	if (!variable[i])
		return (NULL);
	value = ft_calloc(i + 1, sizeof(char));
	i_value = 0;
	while (variable[i])
		value[i_value++] = variable[i++];
	return (1);
}

void	add_varenv(char *new_var)
{
	int		n_lines;
	char	**updated_env;
	char	*new_var;
	char	*tmp;

	tmp = get_varname(new_var);
	if (ft_getenv(tmp))
		unset(tmp);
	free (tmp);
	n_lines = 0;
	while (use_data()->new_env[n_lines])
		n_lines++;
	updated_env = ft_calloc(n_lines + 2, sizeof(char *));
	n_lines = 0;
	while (use_data()->new_env[n_lines])
		updated_env[n_lines] = use_data()->new_env[n_lines];
	updated_env[n_lines] = new_var;
	free (use_data()->new_env);
	use_data()->new_env = updated_env;
}

char	*ft_getenv(char *var_name)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_varname(use_data()->new_env[i]);
	while (use_data()->new_env[i] && ft_strcmp(var_name, tmp) != 0) //check how to write 'strings aren't identical'
	{
		free (tmp);	
		i++;
		tmp = get_varname(use_data()->new_env[i]);
	}
	if (!use_data()->new_env[i])
		return (free (tmp), NULL);
	return (free (tmp), get_varvalue(use_data()->new_env[i]));
}


//exports a new environment variable
int	export_builtin(t_command *cmd)
{

	int		i_cmd;
	int		i_line;

	i_cmd = -1;
	if (!cmd->cmd[1])
		while (use_data()->new_env[++i_cmd])
			print_export(use_data()->new_env[i_cmd]);
	i_cmd = 1;
	i_line = 0;
	while (cmd->cmd[i_cmd])
	{
		if (!ft_isalpha(cmd->cmd[i_cmd][0]) && cmd->cmd[i_cmd][0] != '_')
			tmp_error("minishell : export : \'cmd->cmd[i]\' : not a valid identifier\n");
		while (cmd->cmd[i_cmd][i_line] && cmd->cmd[i_cmd][i_line] != '=')
		{
			if (!ft_isalphanum(cmd->cmd[i_cmd]) && cmd->cmd[i_cmd] != '_')
				return (tmp_error("invalid identifier in export builtin"));
			i_line++;
		}
		add_varenv(ft_strdup(cmd->cmd[i_cmd]));
		i_cmd++;
	}
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

/* calls the relevant function from builtin name, 
or returns 0 if it isn't a builtin.*/
int	check_builtin(t_command *cmd)
{
	char	*lower_cmd;

	lower_cmd = ft_calloc(7, sizeof(char));
	if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "echo"))
		echo_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "cd"))
		cd_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "pwd"))
		pwd_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "export"))
		export_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "unset"))
		unset_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "env"))
		env_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "exit"))
		exit_builtin(cmd);
	else
		return (free(lower_cmd), 0);
	free(lower_cmd);
	return (1);
}
