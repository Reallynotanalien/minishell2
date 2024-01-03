# include "../../../includes/minishell.h"

int	iterate_until_closed(char *str, int *index, char quote)
{
	char	other_quote;

	other_quote = '\'';
	if (quote == '\'')
		other_quote = '\"';
	(*index)++;
	while (str[*index] && str[*index] != quote)
	{
		if (str[*index] == other_quote)
			while (str[*index] && str[*index] != other_quote)
				(*index)++;
		if (!str[*index])
			return (1);
		(*index)++;
	}
	if (!str[*index])
		return (1);
	return (0);
}

//Returns 1 if 'index' is part of a single-quoted string. Else returns 0.
/*Counts the number of single quotes until index is reached,
checks if they are already closed (even number of quotes),
if it is double_quoted (therefore not interpreted) and if there 
is another single quote further in the string. */
int	single_quoted(char *str, int index)
{
	int	*i;

	i = ft_calloc(1, sizeof(int));
	*i = 0;
	while (*i < index)
	{
		if (str[*i] == '\'')
			if(iterate_until_closed(str, i, '\''))
				return (free(i), -1);
		if (*i > index)
			return (free(i), 1);
		if (str[*i] == '\"')
			if(iterate_until_closed(str, i, '\"'))
				return (free (i), -1);
		(*i)++;
	}
	free (i);
	return (0);
}

//Returns 1 if 'index' is part of a double-quoted string. Else returns 0.
int	double_quoted(char *str, int index)
{
	int	*i;

	i = ft_calloc(1, sizeof(int));
	*i = 0;
	while (*i < index)
	{
		if (str[*i] == '\"')
			if(iterate_until_closed(str, i, '\"'))
				return (free(i), -1);
		if (*i > index)
			return (free(i), 1);
		if (str[*i] == '\'')
			if(iterate_until_closed(str, i, '\''))
				return (free (i), -1);
		(*i)++;
	}
	free (i);
	return (0);
}
