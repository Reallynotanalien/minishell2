/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:26:48 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/13 15:50:36 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*If an error is found in the parsing, an error message gets
printed and the error flag gets turned on. The parsing can then 
continue and print as many error messages as it needs without exiting
the program; the flag will get catched at the moment of the execution.*/
int	parsing_error(char *error)
{
	printf("minishell: %s", error);
	use_data()->error_flag = ERROR;
	return (ERROR);
}

void	pipex_error(char *error, int code)
{
	set_exstat(NULL, code);
	perror(error);
}
