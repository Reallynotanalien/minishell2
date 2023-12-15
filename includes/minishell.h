#ifndef MINISHELL_H
# define MINISHELL_H

/*INCLUDES*/
# include <stdio.h>
# include "libft/libft.h"
# include "./readline/history.h"
# include "./readline/readline.h"
# include "parsing.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

/*VARIABLES*/
# define ERROR 1
# define YES 1
# define NO 0
# define T_STR 1
# define T_SUBST 2
# define T_PIPE 3
# define T_HEREDOC 4
# define T_INFILE 5
# define T_OUTFILE 6
# define T_APPEND 7

/*ERROR MESSAGES*/
# define ARGC_ERROR "No argument should be sent appart from the program's name\n"
# define ENV_ERROR "The environment could not be copied\n"
# define ARGV_ERROR "There is no argv\n"
# define FIND_PATH_ERROR "Path was not found\n"

/*STRUCTS*/

typedef struct s_command
{
	int					infile;
	int					outfile;
	char				*path;
	char				**cmd;
	struct s_command	*next;
}					t_command;

//This struct represents the tokens used for each readline return.
//They are seperated in different types defined in VARIABLES.
typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

//This will be the main static struct, to be modified as we go!
typedef struct s_data
{
	struct s_token		*token;
	struct s_command	*cmd;
	char				*error_source;
	int					error_flag;
	int					heredoc_flag;
	int					exstat;
	int					infile;
	int					outfile;
	int					fd[2];
	int					pid;
	int					child;
	int					old_stdin;
	int					old_stdout;
	char				**new_env;
	char				*line;
	char				*line_cpy;
	struct termios		old_attributes;
	struct termios		new_attributes;
}				t_data;

//FUNCTIONS

//build_commands_utils.c
int			open_heredoc(t_token *tokens);
int			contains_whitespace(char *str);

//init.c
void		init_data(t_data *data);

//utils.c
t_data		*use_data(void);
void		view_list(void);
int			find_index(char *str, char target);
char		*ft_strlower(char *str);
char		*ft_getenv(char *var_name);
void		print_array(void);
void		safe_free(void **ptr);
void		clean_data(void);
void		set_exstat(int *status);

//linked_list.c
t_token		*add_token(char *token);
void		free_tokens_if_not_empty(void);
t_token		*lstget_prev(t_token *lst, t_token *reference);

//command_list.c
t_command	*create_command(void);
t_command	*add_command(char *command, int infile, int outfile);
void		free_commands_if_not_empty(void);
void		view_commands(void);

//path.c
char		*access_path(t_command *cmd, char **path_env);
char		*find_path(t_command **cmd, char **env);
t_command	*find_cmd(t_command **cmd);
char		*get_path(t_command *cmd);

int			env_builtin(void);
int			unset_var(char *variable);
int			is_envvar(char	*varname);
void		child_handler(int signum);
void		heredoc_handler(int signum);

//redirections
int			token_redirin(t_token *token);
int			token_redirout(t_token *token);
int			token_redirappend(t_token *token);

void		interruption_handler(int signum);

/*BUILTINS*/
//builtins_utils
char		*ft_lowerbuiltin(char *str, char *buff);
int			confirm_builtin(char **cmd);
int			check_builtin(char **cmd);
int			isvalid_varname(char *variable_name);

//builtins
int			echo_builtin(char **cmd);
int			cd_builtin(char **cmd);
int			pwd_builtin();
int			unset_builtin(char **cmd);
int			exit_builtin(char **cmd);

//export_builtin
char		*get_varname(char *variable);
char		*get_varvalue(char *variable);
int			export_builtin(char **cmd);

/*EXEC*/

//exec_utils
int			count_commands(t_command *cmd);
void		dup_infile(t_command **cmd);
void		dup_outfile(t_command **cmd);
void		reset_files(void);

//exec
void		exec(t_command *cmd);

#endif