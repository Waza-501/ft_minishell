#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		ft_putstr_fd("A malloc error occured, existing the program \n", 2);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
