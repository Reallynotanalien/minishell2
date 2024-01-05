#include "../includes/minishell.h"
#include "../includes/parsing.h"

t_data	*use_data(void)
{
	static t_data	*data;

	if (data == NULL)
	{
		data = malloc(sizeof(t_data));
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
		free (tmp);
		tmp = get_varname(use_data()->new_env[i]);
		i++;
	}
	if (i == 0)
		i = 1;
	if (!ft_strcmp(var_name, tmp))
		return (free (tmp), get_varvalue(use_data()->new_env[i - 1]));
	else
		return (NULL);
	return (NULL);
}
