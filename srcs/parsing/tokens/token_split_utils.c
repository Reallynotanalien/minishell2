/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:33:20 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/05 20:24:59 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*Returns yes if the character is a redirection character
(|, < or >).*/
int	is_redirection(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (YES);
	return (NO);
}

/*Returns yes if the character is a double quote.*/
int	is_double_quote(char c)
{
	if (c == '"')
		return (YES);
	return (NO);
}

/*Copies the part of the command line that we want as a token and
deletes all of the superfluous whitespaces that would be before or
after the string. 
Then the token gets created and the string is freed.*/
void	new_token(int start, int end)
{
	char	*token;

	token = ft_substr(use_data()->line_cpy, start, (end - start + 1));
	token = ft_strtrim_whitespaces(token);
	add_token(token);
	free(token);
}
