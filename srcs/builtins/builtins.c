#include "../../includes/minishell.h"

//checks if the given string is a builtin name.

//calls the relevant function from builtin name.
// int	choose_builtin(char *cmd)
// {

// }

// //print the args on cmd->outfile
// int	echo_builtin(t_command *cmd)
// {
// 	int	i;

// 	i = 1;
// 	while (cmd->cmd[i])
// 		ft_putstr_fd(cmd->cmd[i], cmd->outfile);
// 	if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n"))
// 		ft_putchar_fd('\n', cmd->outfile);
// 	return (0);
// }

// //changes current working directory (env ? check allowed functions !)
// int	cd_builtin(t_command *cmd)
// {
// 	if (!cmd->cmd[1] || cmd->cmd[2])
// 		print_error("error with cd; too many or too few args");
// 	if (!chdir(cmd->cmd[1]))
// 		perror("ERROR : ");

// }

//print current working directory on cmd->outfile
// int	pwd_builtin(t_command *cmd)
// {
// 	char	*cwd;

// 	if (cmd->cmd[1])
// 		print_error("too many args for pwd");
// 	cwd = getcwd(NULL, 0); //apparently this works and would allocate the correct size, but it will require some testing.
// 	ft_putstr_fd(cwd, cmd->outfile);
// 	free (cwd);
// 	return (0);
// }

// //exports a new environment variable
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
