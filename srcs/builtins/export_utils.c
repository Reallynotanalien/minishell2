#include "../../includes/minishell.h"

char	*get_varname(char *variable)
{
	int		i;
	char	*var_name;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	ft_memcpy(var_name, variable, i);
	return (var_name);
}

char	*get_varvalue(char *variable)
{
	int		i;
	char	*value;

	if (!variable)
		return (NULL);
	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	if (!variable[i])
		return (NULL);
	value = ft_calloc((ft_strlen((variable)) - i) + 1, sizeof(char));
	i ++;
	ft_memcpy(value, &variable[i], ft_strlen(variable) - i);
	return (value);
}
