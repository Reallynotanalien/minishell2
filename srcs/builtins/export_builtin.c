
#include "../../includes/minishell.h"

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
			printf("%c", env_var[i]);
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
	return (value);
}

void	add_varenv(char *add_var)
{
	int		n_lines;
	char	**updated_env;
	char	*tmp;

	tmp = get_varname(add_var);
	if (ft_getenv(tmp))
		unset_builtin(tmp);
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

int	export_builtin(t_command *cmd)
{
	int		i_cmd;
	int		i_line;
	char	*var_name;

	i_cmd = -1;
	if (!cmd->cmd[1])
		while (use_data()->new_env[++i_cmd])
			print_export(use_data()->new_env[i_cmd]);
	i_cmd = 1;
	i_line = 0;
	while (cmd->cmd[i_cmd])
	{
		var_name = get_varname(cmd->cmd[i_cmd]);
		if (!isvalid_varname(var_name))
			return (tmp_error("invalid identifier in export builtin"), 1);
		add_varenv(ft_strdup(cmd->cmd[i_cmd]));
		i_cmd++;
	}
	return (0);
}
