/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:29:35 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/09 17:44:20 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo_builtin(char	**cmd)
{
	int	i_cmd;
	int	i_line;

	if (!cmd[1])
		ft_putchar_fd('\n', STDOUT_FILENO);
	i_cmd = 1;
	if (cmd[1] && cmd[1][0] && !ft_strncmp(cmd[1], "-n", 2))
		i_cmd++;
	while (cmd[i_cmd])
	{
		while (cmd[i_cmd] && !cmd[i_cmd][0])
			i_cmd++;
		i_line = -1;
		while (cmd[i_cmd] && cmd[i_cmd][++i_line])
			ft_putchar_fd(cmd[i_cmd][i_line], STDOUT_FILENO);
		if (cmd[i_cmd])
		{
			if (cmd[i_cmd + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i_cmd++;
		}
	}
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2))
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	cd_builtin(char **cmd)
{
	char	*tmp;

	if (!use_data()->new_env || !use_data()->new_env[0])
		return (0);
	if (!cmd[1])
	{
		tmp = ft_getenv("HOME");
		if (chdir(tmp))
			return (ft_printf(2, "minishell: cd: HOME not set\n"),
				set_exstat(NULL, 1), free(tmp), 1);
		free (tmp);
	}
	else if (chdir(cmd[1]) == -1)
		return (perror("minishell: cd: "), set_exstat(NULL, 1), 1);
	return (0);
}

int	pwd_builtin(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free (cwd);
	return (0);
}
