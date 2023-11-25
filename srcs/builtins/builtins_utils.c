
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

/* calls the relevant function from builtin name, 
or returns 0 if it isn't a builtin.*/
int	check_builtin(t_command *cmd)
{
	char	*lower_cmd;

	lower_cmd = ft_calloc(7, sizeof(char));
	if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "echo"))
		echo_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "cd"))
		cd_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "pwd"))
		pwd_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "export"))
		export_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "unset"))
		unset_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "env"))
		env_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "exit"))
		exit_builtin(cmd);
	else
		return (free(lower_cmd), 0);
	free(lower_cmd);
	return (1);
}