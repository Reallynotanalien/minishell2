#include "../../includes/minishell.h"

//checks if the given string is a builtin name.

//returns a char * of the string in lower caps, not allocated.
char	*ft_lowerbuiltin(char *str)
{
	int		i;
	char	new_str[7];

	i = 0;
	while (i < 7)
		new_str[i] = 0;
	i = -1;
	while (str[++i])
		new_str[i] = ft_tolower(str[i]);
	return (new_str);
}

/* calls the relevant function from builtin name, 
or returns 0 if it isn't a builtin.*/
int	check_builtin(t_command *cmd)
{
	char	*lower_cmd;

	if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0]), "echo"))
		echo_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0]), "cd"))
		cd_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0]), "pwd"))
		pwd_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0]), "export"))
		export_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0]), "unset"))
		unset_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0]), "env"))
		env_builtin(cmd);
	else if (!ft_strcmp(ft_lowerbuiltin(cmd->cmd[0]), "exit"))
		exit_builtin(cmd);
	else
		return (0);
	return (1);
}

//print the args on STDOUT_FILENO
int	echo_builtin(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
		ft_putstr_fd(cmd->cmd[i], STDOUT_FILENO);
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
	free (cwd);
	return (0);
}

//exports a new environment variable
int export_builtin()
{

}

//unsets an environment variable
int unset_builtin()
{

}

//prints env
int	env_builtin()
{

}

//gracefully exits minishell
int exit_builtin()
{

}
