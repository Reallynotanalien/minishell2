
#include "../includes/minishell.h"

void	safe_free_ptr(void ***ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		safe_free ((void **)&(array[i]));
	safe_free_ptr((void ***)&array);
}
