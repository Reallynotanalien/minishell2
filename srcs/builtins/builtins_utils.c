
#include "../../includes/minishell.h"

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

int	confirm_builtin(char **cmd)
{
	char	*lower_cmd;

	lower_cmd = ft_calloc(7, sizeof(char));
	if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "echo"))
		return (1);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "cd"))
		return (1);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "pwd"))
		return (1);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "export"))
		return (1);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "unset"))
		return (1);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "env"))
		return (1);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "exit"))
		return (1);
	else
		return (free(lower_cmd), 0);
	free(lower_cmd);
	return (1);
}


/* calls the relevant function from builtin name, 
or returns 0 if it isn't a builtin.*/
int	check_builtin(char **cmd)
{
	char	*lower_cmd;

	lower_cmd = ft_calloc(7, sizeof(char));
	if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "echo"))
		echo_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "cd"))
		cd_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "pwd"))
		pwd_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "export"))
		export_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "unset"))
		unset_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "env"))
		env_builtin();
	else if (!ft_strcmp(ft_lowerbuiltin(cmd[0], lower_cmd), "exit"))
		exit_builtin(cmd);
	else
		return (free(lower_cmd), 0);
	free(lower_cmd);
	return (1);
}

int	isvalid_varname(char *variable_name)
{
	int	i;

	i = -1;
	if (!ft_isalpha(variable_name[0]) && variable_name[0] != '_')
		return (0);
	while (variable_name[++i])
	{
		if (!ft_isalnum(variable_name[i]) && variable_name[i] != '_')
			return (0);
	}
	return (1);
}

int	is_envvar(char	*varname)
{
	int		i;
	char	*tmp;

	i = -1;
	while (use_data()->new_env[++i])
	{
		tmp = get_varname(use_data()->new_env[i]);
		if (!ft_strcmp(varname, tmp))
			return (1);
		free (tmp);
	}
	return (0);
}
