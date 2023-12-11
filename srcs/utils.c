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

void	view_list(void)
{
	t_token	*tokens;
	int		i;

	i = 1;
	tokens = use_data()->token;
	while (tokens)
	{
		printf("----------------\n");
		printf("token%d:[%s]\n", i++, (char *)tokens->token);
		printf("type: %d\n", tokens->type);
		if (!tokens->next)
			return ;
		tokens = tokens->next;
	}
}

char	*ft_strlower(char *str)
{
	int		i;
	char	*new_str;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = -1;
	while (str[++i])
		new_str[i] = ft_tolower(str[i]);
	return (new_str);
}

//returns the index of the first occurence of 'target' in 'str'.
int	find_index(char *str, char target)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != target)
		index ++;
	if (str[index] == target)
		return (index);
	else
		return (-1);
}

char	*ft_getenv(char *var_name)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = get_varname(use_data()->new_env[0]);
	while (use_data()->new_env[++i] && ft_strcmp(var_name, tmp))
	{
		free (tmp);
		tmp = get_varname(use_data()->new_env[i]);
	}
	if (!ft_strcmp(var_name, tmp))
		return (free (tmp), get_varvalue(use_data()->new_env[i - 1]));
	else
		return (NULL);
}

void	print_array(void)
{
	int	i;

	i = -1;
	while (use_data()->new_env[++i])
		printf("%s\n", use_data()->new_env[i]);
}
