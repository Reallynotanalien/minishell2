
#include "../../includes/minishell.h"

char	**cpy_doublearray(char **array)
{
	char	**new_array;
	int		i;

	i = 0;
	while (array[i])
		i++;
	new_array = ft_calloc(i + 1, sizeof (char *));
	i = -1;
	while (array[++i])
		new_array[i] = ft_strdup(array[i]);
	return (new_array);
}

//use "bubble sort" (swap two adjacent elements if they aren't in the right order). Check if char **env_cpy = env, env_cpy[i] = env_cpy[i] + 1 changes the order in env - YES IT DOES D:
char	**sort_env(char **env)
{
	char	**sorted_env;
	char	*tmp;
	int		i;

	sorted_env = cpy_doublearray(env);
	i = 0;
	while (sorted_env[i + 1])
	{
		if (ft_strcmp(sorted_env[i], sorted_env[i + 1]) > 0)
		{
			tmp = sorted_env[i];
			sorted_env[i] = sorted_env[i + 1];
			sorted_env[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (sorted_env);
}

void	print_export(void)
{
	int		i;
	char	**sorted_env;
	char	*var_name;
	char	*var_value;

	i = -1;
	sorted_env = sort_env(use_data()->new_env);
	while (sorted_env[++i])
	{
		var_name = get_varname(sorted_env[i]);
		var_value = get_varvalue(sorted_env[i]);
		if (var_value)
			printf("declare -x %s=\"%s\"\n", var_name, var_value);
		else
			printf("declare -x %s\n", sorted_env[i]);
		free (var_name);
		free (var_value);
	}
	free (sorted_env);
}

char	*get_varname(char *variable)
{
	int		i;
	char	*var_name;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	ft_memcpy(var_name, variable, i);
	return (var_name);
}

char	*get_varvalue(char *variable)
{
	int		i;
	char	*value;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	if (!variable[i])
		return (NULL);
	value = ft_calloc((ft_strlen((variable)) - i) + 1, sizeof(char));
	i ++;
	ft_memcpy(value, &variable[i], ft_strlen(variable) - i);
	return (value);
}

void	add_varenv(char *add_var)
{
	int		n_lines;
	char	**updated_env;
	char	*tmp;

	tmp = get_varname(add_var);
	if (is_envvar(tmp))
		unset_var(get_varname(add_var));
	free (tmp);
	n_lines = 0;
	while (use_data()->new_env[n_lines])
		n_lines++;
	updated_env = ft_calloc(n_lines + 2, sizeof(char *));
	n_lines = 0;
	while (use_data()->new_env[n_lines])
	{
		tmp = use_data()->new_env[n_lines];
		updated_env[n_lines] = ft_strdup(use_data()->new_env[n_lines]);
		free (tmp);
		n_lines++;
	}
	updated_env[n_lines] = add_var;
	free (use_data()->new_env);
	use_data()->new_env = updated_env;
}

int	export_builtin(char **cmd)
{
	int		i_cmd;
	int		i_line;
	char	*var_name;

	if (!use_data()->new_env || !use_data()->new_env[0])
		return (0);
	if (!cmd[1])
		print_export();
	i_cmd = 1;
	i_line = 0;
	while (cmd[i_cmd])
	{
		var_name = get_varname(cmd[i_cmd]);
		if (!isvalid_varname(var_name))
		{
			printf("minishell: export: '%s': is not a valid identifier\n",
				cmd[i_cmd]);
			return (1);
		}
		add_varenv(ft_strdup(cmd[i_cmd]));
		i_cmd++;
		free(var_name);
	}
	return (0);
}
