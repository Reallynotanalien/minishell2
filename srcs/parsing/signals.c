/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:34:01 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 15:51:10 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
1- Suppression of the "unused variable" warning for signum parameter.
2- Ensuring the program's output appears on a new line with printf "\n".
3- Informing Readline that a new line has started (to maintain proper
command line editing and input handling).
4- Clearing the current input line and replacing content with an empty string.
5- Instructing Readline to redisplay the prompt & cleared input line (this is
necessary to ensure the terminal is in the correct state after SIGINT). */
void	interruption_handler(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	child_handler(int signum)
{
	(void) signum;
}

void	sigquit_handler(int signum)
{
	(void) signum;
	printf("^\\Quit: 3\n");
}

/*Exits the child we created to open the heredoc so the read function
stops looking for input.*/
void	heredoc_handler(int signum)
{
	(void) signum;
	if (use_data()->here_doc_str)
		safe_free((void **)&(use_data()->here_doc_str));
	if (use_data()->heredoc_token)
		safe_free((void **)&(use_data()->heredoc_token));
	if (use_data()->heredoc_cmd)
		safe_free((void **)&(use_data()->heredoc_cmd));
	close (use_data()->temp_file);
	exit_program(1);
}

/*Since we do not want the ^C characters to be echoed when we press Ctrl+C,
the terminal's attributes are modified to mute this echo.
If the SIGINT signal (Ctrl+C) is pressed, the interruption_handler
takes care of it. 
If the SIGQUIT signal (Ctrl+\) is pressed, nothing happens (it is
ignored), avoiding the default behavior of quitting and generating
a core dump.*/
void	signals(void)
{
	disable_ctrlc();
	signal(SIGINT, interruption_handler);
	signal(SIGQUIT, SIG_IGN);
}
