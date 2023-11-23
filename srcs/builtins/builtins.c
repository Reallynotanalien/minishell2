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

//not sure this is finished ?
int	set_varname(char *cmd, char *buffer)
{
	int	i;

	i = 0;
	While(cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalphanum(cmd[i]) && cmd[i] != '_')
			return (0);
		buffer[i] = cmd[i];
		i++;
	}
	return (0);
}

int	set_varvalue(char *cmd, char *buffer)
{
	//get everything after first '=' and build a string with it. (use ft_strchr to find begining ?)
}

char	*build_var(char *name, char *value)
{
	//build char *"name=value"
}

void	add_varenv(char *name, char *value)
{
	int		n_lines;
	char	**updated_env;
	char	*new_var;

	if (ft_getenv(name))
		unset(name);
	n_lines = 0;
	while (use_data()->new_env[n_lines])
		n_lines++;
	updated_env = ft_calloc(n_lines + 2, sizeof(char *));
	n_lines = 0;
	while(use_data()->new_env[n_lines])
		updated_env[n_lines] = use_data()->new_env[n_lines];
	new_var = ft_calloc(ft_strlen(name) + ft_strlen(value) + 2, sizeof(char));
	updated_env[n_lines] = build_var(name, value);
	free (use_data()->new_env);
	use_data()->new_env = updated_env;
}

/*everything after '=' is the value of the variable, and before is it's name. The name of an environment variable must follow these rules : 
only letters, digits and '_', cannot start with a digit, and is case sensitive. Messing with a variable used by the system (ex : PATH) might cause problems, and setting a max_lenght could be pertinent.
Multiple variables can be set at the same time. They are delimited by whitespace.*/
//step 1 : check if name is valid. 2 : check if value is valid. 3 : set the value ! 4 : Restart with subsequent variables if necessary.
//export HI=HELLO $HI=10 would use the previous value of HI, not HELLO (This should work as expected as substitutions are done in the begining)
//exports a new environment variable
int	export_builtin(t_command *cmd)
{
	int		i_cmd;
	int		i_line;
	char	*var_name;
	char	*var_value;

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
		if (ft_strchr(cmd->cmd[i_cmd], '=') == 0)
			var_name = ft_calloc(ft_strlen(cmd->cmd[i_cmd]) + 1, sizeof(char));
		else
			var_name = ft_calloc(ft_strchr(cmd->cmd[i_cmd], '=') + 1, sizeof(char));
		if (!set_varname(cmd->cmd[i_cmd], var_name))
			return(tmp_error("export : invalid identifier\n"));
		if (!set_varvalue(cmd->cmd[i_cmd], var_value))
		{
			if (!ft_getenv(var_name))
				//add variable to env with value ""
			return(tmp_error("export : invalid identifier\n"));
		}
		add_varenv(var_name, var_value);
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
