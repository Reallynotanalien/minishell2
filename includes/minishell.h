/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:28:26 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/14 14:46:20 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*INCLUDES*/
# include <stdio.h>
# include "libft/libft.h"
# include "./readline/history.h"
# include "./readline/readline.h"
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
# define HD_FORK_ERROR "minishell: heredoc: could not fork\n"
# define HD_OPEN_ERROR "minishell: heredoc: could not open heredoc\n"
# define STRDUP_ERROR "Could not duplicate string.\n"
# define QUOTES_ERROR "found unclosed quotation marks\n"

/*STRUCTS*/

typedef struct s_command
{
	int					infile;
	int					outfile;
	char				*path;
	char				**cmd;
	char				*lower_cmd;
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
	char				*here_doc_str;
	struct termios		old_attributes;
	struct termios		new_attributes;
}				t_data;

//FUNCTIONS

//cleaning.c

//cleaning_utils.c
void		safe_free(void **ptr);
void		free_array(char **array);

//init.c
void		init_data(t_data *data);

//utils.c
t_data		*use_data(void);
char		*ft_getenv(char *var_name);
char		**copy_env(char **env);
void		print_array(void);
void		safe_free(void **ptr);
void		set_exstat(int *status, int exstat);
int			iterate_until_closed(char *str, int *index, char quote);
void		clean_cmds(void);
void		free_array(char **array);
void		clean_after_loop(void);
int			is_quote(char check);

/*BUILTINS*/
//builtins_utils.c
int			confirm_builtin(t_command *cmd);
int			check_builtin(t_command *cmd);
int			isvalid_varname(char *variable_name);
int			is_envvar(char	*varname);

//builtins.c
int			echo_builtin(char **cmd);
int			cd_builtin(char **cmd);
int			pwd_builtin(void);
int			unset_var(char *variable);
int			unset_builtin(char **cmd);
int			env_builtin(void);
int			exit_builtin(char **cmd);

//export_builtin.c
char		*get_varname(char *variable);
char		*get_varvalue(char *variable);
int			export_builtin(char **cmd);

/*ERROR*/

//errors.c
int			parsing_error(char *error);
void		exit_program(int code);
void		pipex_error(char *error, int code);

//exit_status.c
int			*get_pid_status(void);
void		set_exstat(int *status, int exstat);

/*EXEC*/

//exec_dup.c
int			count_commands(t_command *cmd);
void		close_files(t_command **cmd);

//exec_utils.c
void		execute(t_command **cmd);
void		dup_infile(t_command **cmd, int copy);
void		dup_outfile(t_command **cmd, int copy);
void		reset_files(void);
void		setup_pipe_outfile(void);
void		setup_pipe_infile(t_command **cmd);

//exec.c
void		exec(t_command *cmd);

//path.c
char		*access_path(t_command *cmd, char **path_env);
char		*find_path(t_command **cmd, char **env);
t_command	*find_cmd(t_command **cmd);
char		*get_path(t_command *cmd);

/*PARSING*/

//parsing.c
void		line_parsing(void);

//signals.c
void		interruption_handler(int signum);
void		child_handler(int signum);
void		heredoc_handler(int signum);
void		signals(void);

//term_attributes.c
void		disable_ctrlc(void);
void		restore_attributes(void);

/*Commands*/

//build_commands_utils.c
int			open_heredoc(t_token *tokens, char *command);
int			contains_whitespace(char *str);

//build_commands.c
int			build_commands(void);

//command_list.c
t_command	*create_command(void);
t_command	*add_command(char *command, int infile, int outfile);
void		free_commands_if_not_empty(void);
void		view_commands(void);

/*Tokens*/

//line_parsing.c
int			parse_quotes(char *str);
int			remove_spaces(char *str);
int			skip_envvar(char *line, int *i, int *flag_var);

//linked_list.c
t_token		*add_token(char *token);
void		free_tokens_if_not_empty(void);
void		view_list(void);

//redirections.c
int			token_redirin(t_token *token);
int			token_redirout(t_token *token);
int			token_redirappend(t_token *token);

//substitutions.c
void		do_substitutions(char *line);

//token_parsing_utils.c
int			double_quoted(char *str, int index);
int			single_quoted(char *str, int index);

//token_parsing.c
int			parsing_redirection(char *line, int index);

//token_split_utils.c
int			is_redirection(char c);
int			is_double_quote(char c);
void		new_token(int start, int end);

//token_split.c
int			split_tokens(void);

#endif