# include "../../../includes/minishell.h"

int	parse_quotes(char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '\'' && !double_quoted(str, i))
			single_quotes++;
	double_quotes = 0;
	i = -1;
	while (str[++i] && !single_quoted(str, i))
		if (str[i] == '\"')
			double_quotes ++;
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (parsing_error(QUOTES_ERROR));
	return (0);
}

int	find_lenght(char *str, int end)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < end && ft_iswhitespace(str[i]))
		i++;
	while (i < end)
	{
		while (i < end && (!ft_iswhitespace(str[i])
				|| double_quoted(str, i) || single_quoted(str, i)))
		{
			i++;
			len++;
		}
		if (i < end)
			len++;
		while (ft_iswhitespace(str[i]))
			i++;
	}
	return (len);
}


char	*skip_consecutives(int i, int end, char *str)
{
	int		i_new;
	char	*new_str;

	new_str = ft_calloc(find_lenght(str, end) + 1, sizeof(char));
	i_new = 0;
	while (i < end)
	{
		while (str[i] && (!ft_iswhitespace(str[i]) 
			|| double_quoted(str, i) || single_quoted(str, i)))
			new_str[i_new++] = str[i++];
		if (i < end)
			new_str[i_new++] = ' ';
		while (ft_iswhitespace(str[i]))
			i++;
	}
	return (new_str);
}

int	remove_spaces(char *str)
{
	int		i;
	int		end;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	end = ft_strlen(str) - 1;
	while (ft_iswhitespace(str[end]))
		end--;
	if (end != i)
		end++;
	if (end == i)
		use_data()->line_cpy = ft_substr(str, i, 1);
	else
		use_data()->line_cpy = skip_consecutives(i, end, str);
	free (str);
	return (EXIT_SUCCESS);
}