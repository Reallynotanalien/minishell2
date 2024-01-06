/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:33:20 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/05 19:33:21 by kafortin         ###   ########.fr       */
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
