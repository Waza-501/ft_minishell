/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 01:01:54 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/25 18:09:26 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		split = ft_split(envp[i], '=');
		if (!split)
			printf("split error encountered. Fix this later\n");
		cdll_add_back(copy, cdll_new_node(split[0], split[1], 0));
		free(split);
		i++;
	}
	printf("%s, %s\n", split[0], split[1]);
	return (copy);
}
