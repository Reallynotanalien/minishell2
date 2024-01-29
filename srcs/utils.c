/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edufour <edufour@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:35:26 by kafortin          #+#    #+#             */
/*   Updated: 2024/01/29 11:34:49 by edufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*use_data(void)
{
	static t_data	*data;

	if (data == NULL)
	{
		data = ft_calloc(1, sizeof(t_data));
		init_data(data);
	}
	return (data);
}

char	*ft_getenv(char *var_name)
{
	char	*tmp;
	int		i;

	if (!use_data()->new_env || !use_data()->new_env[0] || !var_name)
		return (NULL);
	tmp = get_varname(use_data()->new_env[0]);
	i = 0;
	while (use_data()->new_env[i] && ft_strcmp(var_name, tmp))
	{
		safe_free((void **)&tmp);
		tmp = get_varname(use_data()->new_env[i]);
		i++;
	}
	if (i == 0)
		i = 1;
	if (!ft_strcmp(var_name, tmp))
		return (safe_free((void **)&tmp),
			get_varvalue(use_data()->new_env[i - 1]));
	else
		return (safe_free((void **)&tmp), NULL);
	return (free((void **)&tmp), NULL);
}

char	**copy_array(char **old_array)
{
	char	**new_array;
	int		nb_lines;
	int		i;

	nb_lines = 0;
	while (old_array[nb_lines])
		nb_lines++;
	new_array = ft_calloc(nb_lines + 1, sizeof(char *));
	i = -1;
	while (old_array[++i])
		new_array[i] = ft_strdup(old_array[i]);
	return (new_array);
}

int	is_quote(char check)
{
	if (check == '\'' || check == '\"')
		return (1);
	return (0);
}

void	safe_close_file(int fd)
{
	if (fd != 0)
		close (fd);
}
