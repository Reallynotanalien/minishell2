/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:25:49 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/16 13:13:35 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	confirm_builtin(t_command *cmd)
{
	if (cmd->lower_cmd == NULL || cmd->lower_cmd == NULL)
		return (0);
	if (!ft_strcmp(cmd->lower_cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd->lower_cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd->lower_cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->lower_cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd->lower_cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd->lower_cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd->lower_cmd, "exit"))
		return (1);
	else
		return (0);
}

/* calls the relevant function from builtin name, 
or returns 0 if it isn't a builtin.*/
int	check_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->lower_cmd, "echo"))
		use_data()->exstat = echo_builtin(cmd->cmd);
	else if (!ft_strcmp(cmd->lower_cmd, "cd"))
		use_data()->exstat = cd_builtin(cmd->cmd);
	else if (!ft_strcmp(cmd->lower_cmd, "pwd"))
		use_data()->exstat = pwd_builtin();
	else if (!ft_strcmp(cmd->lower_cmd, "export"))
		use_data()->exstat = export_builtin(cmd->cmd);
	else if (!ft_strcmp(cmd->lower_cmd, "unset"))
		use_data()->exstat = unset_builtin(cmd->cmd);
	else if (!ft_strcmp(cmd->lower_cmd, "env"))
		use_data()->exstat = env_builtin();
	else if (!ft_strcmp(cmd->lower_cmd, "exit"))
		use_data()->exstat = exit_builtin(cmd->cmd);
	else
		return (0);
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
	if (!use_data()->new_env || !use_data()->new_env[0])
		return (0);
	while (use_data()->new_env[++i])
	{
		tmp = get_varname(use_data()->new_env[i]);
		if (!ft_strcmp(varname, tmp))
			return (safe_free((void **)&tmp), 1);
		safe_free((void **)&tmp);
	}
	return (safe_free((void **)&tmp), 0);
}
