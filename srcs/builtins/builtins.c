#include "../../includes/minishell.h"

//checks if the given string is a builtin name.

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

//print the args on STDOUT_FILENO
int	echo_builtin(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[++i])
	{
		ft_putstr_fd(cmd->cmd[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n"))
		ft_putchar_fd('\n', STDIN_FILENO);
	return (0);
}

//changes current working directory (env ? check allowed functions !)
int	cd_builtin(t_command *cmd)
{
	if (!cmd->cmd[1] || cmd->cmd[2])
		print_error("error with cd; too many or too few args");
	if (!chdir(cmd->cmd[1]))
		perror("ERROR : ");
}

// print current working directory on STDOUT_FILENO
int	pwd_builtin(t_command *cmd)
{
	char	*cwd;

	if (cmd->cmd[1])
		print_error("too many args for pwd");
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free (cwd);
	return (0);
}

//exports a new environment variable
// int export_builtin()
// {

// }

// //unsets an environment variable
// int unset_builtin()
// {

// }

// //prints env
// int	env_builtin()
// {

// }

// //gracefully exits minishell
// int exit_builtin()
// {

// }

/* calls the relevant function from builtin name, 
or returns 0 if it isn't a builtin.*/
// int	check_builtin(t_command *cmd)
// {
// 	char	*lower_cmd;

// 	lower_cmd = ft_calloc(7, sizeof(char));
// 	if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "echo"))
// 		echo_builtin(cmd);
// 	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "cd"))
// 		cd_builtin(cmd);
// 	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "pwd"))
// 		pwd_builtin(cmd);
// 	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "export"))
// 		export_builtin(cmd);
// 	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "unset"))
// 		unset_builtin(cmd);
// 	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "env"))
// 		env_builtin(cmd);
// 	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0], lower_cmd), "exit"))
// 		exit_builtin(cmd);
// 	else
// 		return (free(lower_cmd), 0);
// 	free(lower_cmd);
// 	return (1);
// }
