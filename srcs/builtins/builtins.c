/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:28:14 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 12:26:26 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env(int i)
{
	while (use_data()->new_env[i])
	{
		free (use_data()->new_env[i]);
		while (use_data()->new_env[i])
		{
			use_data()->new_env[i] = use_data()->new_env[i + 1];
			i++;
		}
	}
}

int	unset_var(char *variable)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!isvalid_varname(variable))
		return (ft_printf(2,
				"minishell: unset: \'%s\': not a valid identifier\n", variable),
			set_exstat(NULL, 1), safe_free((void **)&variable), 1);
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
		return (safe_free((void **)&variable), 0);
	update_env(i);
	return (safe_free((void **)&variable), 0);
}

//unsets an environment variable
//it follows the same rules as naming a variable (alnum, _, no digit first)
int	unset_builtin(char **cmd)
{
	int		i;

	if (!use_data()->new_env || !use_data()->new_env[0])
		return (0);
	i = 0;
	while (cmd[++i])
		unset_var(ft_strdup(cmd[i]));
	return (0);
}

int	env_builtin(void)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!use_data()->new_env || !use_data()->new_env[0])
		return (0);
	tmp = get_varvalue(use_data()->new_env[0]);
	while (use_data()->new_env[++i])
	{
		if (tmp)
			printf("%s\n", use_data()->new_env[i]);
		free (tmp);
		tmp = get_varvalue(use_data()->new_env[i]);
	}
	free(tmp);
	return (0);
}

int	exit_builtin(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1] && cmd[2])
		return (ft_printf(2, "minishell: exit: too many arguments"), 1);
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
			i++;
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]) && cmd[1][i] != '-')
			{
				return (ft_printf(2,
						"minishell: exit: %s: numeric argument required\n",
						cmd[1]), exit_program(255), 0);
			}
			i++;
		}
		return (ft_printf(1, "exit\n"), exit_program((unsigned int)ft_atoi(cmd[1])), 0);
	}
	return (ft_printf(1, "exit\n"), exit_program(0), 0);
}
