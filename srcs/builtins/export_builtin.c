
#include "../../includes/minishell.h"

char	*get_next_var(char *last_var)
{
	int		i;
	char	*next_var;

	i = -1;
	while (use_data()->new_env[++i])
		if (ft_strcmp(use_data()->new_env[i], next_var) < 0
			&& (last_var == NULL
				|| ft_strcmp(use_data()->new_env[i], last_var) > 0))
			next_var = use_data()->new_env[i];
	return (next_var);
}

void	print_export(void)
{
	int		printed;
	int		nb_vars;
	char	*last_var;

	last_var = NULL;
	printed = 0;
	nb_vars = 0;
	while (use_data()->new_env[nb_vars])
		nb_vars++;
	while (printed != nb_vars)
	{
		printf("declare -x ");
		last_var = get_next_var(last_var);
		printf("%s\n", last_var);
		printed++;
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
	return (value);
}

void	add_varenv(char *add_var)
{
	int		n_lines;
	char	**updated_env;
	char	*tmp;

	tmp = get_varname(add_var);
	if (is_envvar(tmp))
		unset_builtin(&add_var);
	free (tmp);
	n_lines = 0;
	while (use_data()->new_env[n_lines])
		n_lines++;
	updated_env = ft_calloc(n_lines + 2, sizeof(char *));
	n_lines = -1;
	while (use_data()->new_env[++n_lines])
		updated_env[n_lines] = use_data()->new_env[n_lines];
	updated_env[n_lines] = add_var;
	free (use_data()->new_env);
	use_data()->new_env = updated_env;
}

int	export_builtin(char **cmd)
{
	int		i_cmd;
	int		i_line;
	char	*var_name;

	i_cmd = -1;
	if (!cmd[1])
		print_export();
	i_cmd = 1;
	i_line = 0;
	while (cmd[i_cmd])
	{
		var_name = get_varname(cmd[i_cmd]);
		if (!isvalid_varname(var_name))
			return (tmp_error("invalid identifier in export builtin"), 1);
		add_varenv(ft_strdup(cmd[i_cmd]));
		i_cmd++;
	}
	return (0);
}
