
#include "../../../includes/minishell.h"

/*The below function test the behavior of tokens surrounded by 
all symbols required to handle in the subject. 
Everything else is considered a string.
If an error should occur because of an invalid string, 
it will be handled by execve.
Only symbols right of the redirection is checked, as the error would 
have been caught earlier if a redirection symbol is present on left*/

int	next_isredirection(char *line, int index)
{
	if (line[index + 1] == ' ' || line[index + 1] == '\t')
		index += 2;
	else
		index++;
	if ((!double_quoted(line, index) && !single_quoted(line, index))
		&& (line[index] == '<' || line[index] == '>' || line[index] == '|'))
		return (1);
	return (0);
}

//For '>>', index is the index of the first '>'.
int	parsing_redirection(char *line, int index)
{
	if (line[index + 1] && line[index] == line[index + 1] && line[index] != '|')
		index ++;
	if (index == 0 && line[index] == '|')
		return (ft_printf(2,
				"minishell: syntax error near unexpected token '|'\n"),
			set_exstat(NULL, 258), ERROR);
	if (!line[index + 1])
		return (ft_printf(2,
				"minishell: syntax error near unexpected token 'newline'\n"),
			set_exstat(NULL, 258), ERROR);
	if (next_isredirection(line, index))
	{
		if (line[index + 1] == ' ' || line[index + 1] == '\t')
			index ++;
		index++;
		if (line[index + 1] && line[index] == line[index + 1])
			return (ft_printf(2,
					"minishell: syntax error near unexpected token '%c%c'\n",
					line[index], line[index]), set_exstat(NULL, 258), ERROR);
		return (ft_printf(2,
				"minishell: syntax error near unexpected token '%c'\n",
				line[index]), set_exstat(NULL, 258), ERROR);
	}
	return (0);
}
