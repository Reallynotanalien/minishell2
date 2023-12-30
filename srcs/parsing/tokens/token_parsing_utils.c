# include "../../../includes/minishell.h"

//Returns 1 if 'index' is part of a single-quoted string. Else returns 0.
/*Counts the number of single quotes until index is reached,
checks if they are already closed (even number of quotes),
if it is double_quoted (therefore not interpreted) and if there 
is another single quote further in the string. */
int	single_quoted(char *str, int index)
{
	int quoted;
	int	i;

	i = 0;
	quoted = -1;
	if (!str[index])
		return (0);
	while (i < index)
	{
		if (str[i] == '\'')
		{
			quoted *= -1;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (-1);
		}
		else	
			i++;
	}
	if (quoted == -1)
		return (0);
	return (quoted);
}

//Returns 1 if 'index' is part of a double-quoted string. Else returns 0.
int	double_quoted(char *str, int index)
{
	int quoted;
	int	i;

	i = 0;
	quoted = -1;
	if (!str[index])
		return (0);
	while (i < index)
	{
		if (str[i] == '\"')
		{
			quoted *= -1;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (-1);
		}
		else	
			i++;
	}
	if (quoted == -1)
		return (0);
	return (quoted);
}