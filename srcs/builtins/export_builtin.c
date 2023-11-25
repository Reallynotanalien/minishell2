
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
			tmp_error("export_builtin invalid identifier");
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