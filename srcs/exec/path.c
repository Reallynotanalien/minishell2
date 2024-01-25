/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:29:17 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/25 13:52:38 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Tests all of the paths in the environnment and return the one
that is executable.*/
char	*access_path(t_command *cmd, char **path_env)
{
	int		i;
	char	*path_join;

	i = 0;
	path_join = NULL;
	while (path_env[i])
	{
		path_join = ft_strjoin(path_env[i], "/");
		cmd->path = ft_strjoin (path_join, cmd->cmd[0]);
		safe_free((void **)&(path_join));
		if (access(cmd->path, F_OK) == 0)
			return (cmd->path);
		safe_free((void **)&(cmd->path));
		cmd->path = NULL;
		i++;
	}
	return (NULL);
}

/*Looks through the environment to find an executable path for the command sent
as an argument.*/
char	*find_path(t_command *cmd, char **env)
{
	int		i;
	char	**path_env;

	if (!use_data()->new_env || !use_data()->new_env[0])
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
		if (env[i] == NULL)
			return (NULL);
	}
	path_env = (char **)ft_split(env[i] + 5, ':');
	i = 0;
	cmd->path = access_path(cmd, path_env);
	free_array(path_env);
	return (cmd->path);
}

/*Looks for the path, checks if it is valid and returns it.*/
t_command	*find_cmd(t_command *cmd)
{
	cmd->path = find_path(cmd, use_data()->new_env);
	if (!cmd->path)
		cmd->path = ft_strdup(cmd->cmd[0]);
	return cmd;
}

/*If we have an absolute path, then we use it as the cmd->path and
return it as is. If not, we find the path and as well as changing 
it directly in the struct, we return it.*/
char	*get_path(t_command *cmd)
{
	if (access(cmd->cmd[0], F_OK | X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->cmd[0]);
	}
	else
		find_cmd(cmd);
	return (cmd->path);
}
