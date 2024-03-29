/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:31:22 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 12:02:05 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*Adds an index number representing the token's type to facilitate
the transfer to the command struct later on. 
1 = T_STR
2 = T_SUBST
3 = T_PIPE
4 = T_HEREDOC
5 = T_INFILE
6 = T_OUTFILE
7 = T_APPEND*/
int	check_type(char *token)
{
	int	type;

	type = 0;
	if (is_redirection(token[0]))
	{
		if (token[0] == '|')
			type = T_PIPE;
		else if (token[0] == '<')
		{
			if (token[1] == '<')
				type = T_HEREDOC;
			else
				type = T_INFILE;
		}
		else if (token[0] == '>')
		{
			if (token[1] == '>')
				type = T_APPEND;
			else
				type = T_OUTFILE;
		}
	}
	else
		type = T_STR;
	return (type);
}

/*Initializes a new token node.*/
t_token	*create_token(void)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

/*Adds a new token node to the linked list and places it at the
end of the list. Copies the string sent as an argument in the 
token attribute. Then checks for the token type.*/
t_token	*add_token(char *token)
{
	t_token	*new;
	t_token	*next;

	if (token == NULL)
		return (NULL);
	new = create_token();
	if (!new)
		return (NULL);
	new->token = token;
	new->type = check_type(token);
	if (use_data()->token == NULL)
		use_data()->token = new;
	else
	{
		next = use_data()->token;
		while (next->next != NULL)
			next = next->next;
		next->next = new;
	}
	return (use_data()->token);
}
