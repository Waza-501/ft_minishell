/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 01:01:54 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/27 18:11:31 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mem(char **data)
{
	int	idx;

	idx = 0;
	while (data[idx])
	{
		free(data[idx]);
		idx++;
	}
	free(data);
}

char	**ft_split_env(char const *s, char c)
{
	char	*copy;
	char	**ret;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (3));
	if (!ret)
		return (NULL);
	ret[2] = NULL;
	copy = ft_strdup(s);
	while (*copy && c == *copy)
		copy++;
	while (copy[i] && c != copy[i])
		i++;
	ret[0] = ft_substr(copy, 0, i);
	i++;
	ret[1] = ft_substr(&copy[i], 0, ft_strlen(copy));
	free(copy);
	return (ret);
}

int	find_env_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

t_cdllist	*copy_envp(char **envp)
{
	t_cdllist	*copy;
	char		**split;
	int			i;

	i = 0;
	if (!envp)
		return (NULL);
	copy = cdll_init_list();
	if (!copy)
		return (NULL);
	while (envp[i])
	{
		split = ft_split_env(envp[i], '=');
		if (!split)
			printf("split error encountered. Fix this later\n");
		cdll_add_back(copy, cdll_new_node(split[0], split[1], 0));
		free(split);
		i++;
	}
	return (copy);
}
