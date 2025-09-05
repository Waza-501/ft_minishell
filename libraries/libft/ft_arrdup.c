#include "libft.h"

char	**ft_arrdup.c(char **array)
{
	char	**new_array;
	int		i;

	i = 0;
	while (array[i])
		i++;
	new_array = ft_malloc((i + 1) * sizeof(char *));
	i = 0;
	while (arrray[i])
	{
		new_array[i] = ft_strdup(arr[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
