# include "../../includes/minishell.h"

/*Tests all of the paths in the environnment and return the one
that is executable.*/
char	*access_path(t_command *cmd, char **path_env)
{
	int		i;
	char	*path_join;

	i = 0;
	while (path_env[i])
	{
		path_join = ft_strjoin(path_env[i], "/");
		cmd->path = ft_strjoin (path_join, cmd->cmd[0]);
		free(path_join);
		if (access(cmd->path, F_OK) == 0)
			return (cmd->path);
		free(cmd->path);
		cmd->path = NULL;
		i++;
	}
	return (NULL);
}

/*Looks through the environment to find an executable path for the command sent
as an argument.*/
char	*find_path(t_command **cmd, char **env)
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
		if (env[i] == NULL || env[i + 1] == NULL)
			return (NULL);
	}
	path_env = (char **)ft_split(env[i] + 5, ':');
	i = 0;
	(*cmd)->path = access_path(*cmd, path_env);
	return ((*cmd)->path);
}

/*Looks for the path, checks if it is valid and returns it.*/
t_command	*find_cmd(t_command **cmd)
{
	(*cmd)->path = find_path(cmd, use_data()->new_env);
	if ((*cmd)->path == NULL || access((*cmd)->path, X_OK) == -1)
	{
		ft_printf(2, "minishell: %s: command not found\n", (*cmd)->cmd[0]);
		use_data()->error_flag = ERROR;
		use_data()->exstat = 127;
	}
	return (*cmd);
}

/*If we have an absolute path, then we use it as the cmd->path and
return it as is. If not, we find the path and as well as changing 
it directly in the struct, we return it.*/
char	*get_path(t_command *cmd)
{
	DIR	*ptr;

	ptr = opendir(cmd->cmd[0]);
	if (ptr)
	{
		ft_printf(2, "minishell: %s: is a directory\n", cmd->cmd[0]);
		use_data()->error_flag = ERROR;
		use_data()->exstat = 126;
	}
	else if (access(cmd->cmd[0], F_OK | X_OK) == 0)
		cmd->path = cmd->cmd[0];
	else
		find_cmd(&cmd);
	return (cmd->path);
}
