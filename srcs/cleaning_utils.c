/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:34:17 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/05 19:34:19 by kafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

void	free_array(char ***array)
{
	int	i;

	i = 0;
	if (!array || !(*array))
		return ;
	while (*(array)[i])
	{
		safe_free((void **)&((*array)[i]));
		i++;
	}
	free((void **)array);
}
