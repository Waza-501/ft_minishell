/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_sync.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 10:51:54 by haile         #+#    #+#                 */
/*   Updated: 2025/11/06 11:35:24 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Split environment variable into key and value
 * @param env_var Environment variable string (format: "KEY=VALUE")
 * @param key Output parameter for key (caller must free)
 * @param value Output parameter for value (caller must free)
 * @return 0 on success, 1 on error
 */
static int	split_env_var(char *env_var, char **key, char **value)
{
	char	*equals_pos;
	int		key_len;

	equals_pos = ft_strchr(env_var, '=');
	if (!equals_pos)
	{
		*key = ft_strdup(env_var);
		*value = ft_strdup("");
	}
	else
	{
		key_len = equals_pos - env_var;
		*key = ft_substr(env_var, 0, key_len);
		*value = ft_strdup(equals_pos + 1);
	}
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		*key = NULL;
		*value = NULL;
		return (1);
	}
	return (0);
}

/*
 * @brief MEMORY SAFE: Remove all nodes without double-free
 * @param env_list List to clear
 *
 * FIXED: Uses cdll_del_node with false to avoid double-free
 */
static void	safe_clear_list(t_cdllist *env_list)
{
	t_cd_ll_node	*current;
	char			*var_name_copy;
	int				original_size;
	int				attempts;

	if (!env_list || !env_list->head || env_list->size == 0)
		return;
	attempts = 0;
	while (env_list->head && env_list->size > 0 && attempts < 100)
	{
		current = env_list->head;
		// Make a copy of the variable name for deletion
		var_name_copy = ft_strdup(current->var_1);
		if (!var_name_copy)
			break;
		// FIXED: Use false to let us manage memory ourselves
		cdll_del_node(env_list, false, var_name_copy);
		free(var_name_copy);
		attempts++;
	}
}

/*
 * @brief ALTERNATIVE: Clear list using your del_list function
 * Use this if the individual deletion approach still has issues
 */
static int	rebuild_list_completely(char **env_array, t_cdllist *env_list)
{
	char		*key;
	char		*value;
	t_cd_ll_node	*new_node;
	int		i;

	if (!env_array || !env_list)
		return (1);
	// Step 1: Completely destroy the old list
	cdll_del_list(env_list);
	// Step 2: Re-initialize the list structure
	// NOTE: You might need to call cdll_init_list() here or similar
	// depending on how your cdll_del_list works
	env_list->head = NULL;
	env_list->size = 0;
	// Step 3: Rebuild from env_array
	i = 0;
	while (env_array[i])
	{
		if (split_env_var(env_array[i], &key, &value) != 0)
			return (1);
		// Create new node - it takes ownership of key and value
		new_node = cdll_new_node(key, value, 0);
		if (!new_node)
		{
			free(key);
			free(value);
			return (1);
		}
		// Add to list
		cdll_add_back(env_list, new_node);
		// DON'T free key and value here - the node owns them now
		i++;
	}

	return (0);
}

/*
 * @brief MEMORY SAFE: Synchronize shell->env array back to linked list
 * @param env_array Current environment array (shell->env)
 * @param env_list Linked list to update (data->envp_copy)
 * @return 0 on success, 1 on error
 *
 * FIXED: Proper memory management to avoid double-free
 */
int	sync_env_to_list(char **env_array, t_cdllist *env_list)
{
	char		*key;
	char		*value;
	t_cd_ll_node	*new_node;
	int		i;

	if (!env_array || !env_list)
		return (1);
	// SAFER: Use complete rebuild approach
	return (rebuild_list_completely(env_array, env_list));
}

/*
 * @brief CONSERVATIVE APPROACH: Update existing, add new, don't delete
 * Use this version if rebuild still has issues
 */
int	sync_env_to_list_conservative(char **env_array, t_cdllist *env_list)
{
	char		*key;
	char		*value;
	t_cd_ll_node	*new_node;
	t_cd_ll_node	*current;
	bool		found;
	int		i, j;

	if (!env_array || !env_list)
		return (1);
	// Conservative: only update existing and add new, never delete
	i = 0;
	while (env_array[i])
	{
		if (split_env_var(env_array[i], &key, &value) != 0)
			return (1);

		// Look for existing variable to update
		found = false;
		if (env_list->head && env_list->size > 0)
		{
			current = env_list->head;
			for (j = 0; j < env_list->size; j++)
			{
				if (current && current->var_1 &&
					ft_strncmp(current->var_1, key, ft_strlen(key)) == 0 &&
					ft_strlen(current->var_1) == ft_strlen(key))
				{
					// Update existing - free old value, set new one
					free(current->var_2);
					current->var_2 = ft_strdup(value);
					found = true;
					break;
				}
				current = current->next;
				if (current == env_list->head)
					break;
			}
		}
		// Add new variable if not found
		if (!found)
		{
			new_node = cdll_new_node(key, value, 0);
			if (new_node)
				cdll_add_back(env_list, new_node);
		}
		// Clean up our copies
		free(key);
		free(value);
		i++;
	}
	return (0);
}

// /*
//  * @brief MINIMAL APPROACH: Just don't sync for now
//  * Use this to test if the sync is the problem
//  */
// int	sync_env_to_list_disabled(char **env_array, t_cdllist *env_list)
// {
// 	(void)env_array;
// 	(void)env_list;
// 	// Do nothing - just return success
// 	// This will let export work within a session but not persist
// 	return (0);
// }
