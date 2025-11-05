/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_sort.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 15:51:38 by haile         #+#    #+#                 */
/*   Updated: 2025/11/05 15:52:32 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Count the number of environment variables
 * @param env Environment array (NULL-terminated)
 * @return Number of variables
 */
static int	count_env(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}

/*
 * @brief Create a duplicate of the environment array
 * @param env Source environment array
 * @return Duplicated array (caller must free)
 */
static char	**dup_env(char **env)
{
	char	**dup;
	int		i;
	int		size;

	size = count_env(env);
	dup = ft_malloc((size + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = ft_strdup(env[i]);
		if (!dup[i])
		{
			// Cleanup on failure
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[size] = NULL;
	return (dup);
}

/*
 * @brief Swap two string pointers
 * @param a First string pointer
 * @param b Second string pointer
 */
static void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * @brief Sort environment array alphabetically using selection sort
 * @param env Environment array to sort (modified in place)
 *
 * Uses selection sort (O(n²) but simple and env arrays are small)
 * Compares variable names only (before '=' sign)
 */
static void	sort_array(char **env)
{
	int		i;
	int		j;
	int		min_idx;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		min_idx = i;
		j = i + 1;
		while (env[j])
		{
			// Compare only the variable name (before '=')
			if (ft_strncmp(env[j], env[min_idx],
				ft_strchr(env[j], '=') - env[j]) < 0)
				min_idx = j;
			j++;
		}
		if (min_idx != i)
			swap_strings(&env[i], &env[min_idx]);
		i++;
	}
}

/*
 * @brief Create a sorted copy of the environment array
 * @param env Source environment array
 * @return Sorted copy (caller must free each string + array)
 *
 * Steps:
 * 1. Duplicate the environment array
 * 2. Sort the duplicate alphabetically
 * 3. Return sorted copy (original untouched)
 */
char	**sort_env(char **env)
{
	char	**sorted;

	sorted = dup_env(env);
	if (!sorted)
		return (NULL);
	sort_array(sorted);
	return (sorted);
}
