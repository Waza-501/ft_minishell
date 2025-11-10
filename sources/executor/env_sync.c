/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_sync.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 10:51:54 by haile         #+#    #+#                 */
/*   Updated: 2025/11/10 12:39:48 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief OPTION 1: DISABLED SYNC (Safest for testing)
 * Use this to test if export works without persistence
 */
int	sync_env_to_list_disabled(char **env_array, t_cdllist *env_list)
{
	(void)env_array;
	(void)env_list;
	return (0); // Do nothing - variables won't persist between commands
}

/**
 * @brief OPTION 2: CONSERVATIVE SYNC (Add/update only, no deletion)
 * Use this if you want basic persistence without complex memory management
 */
int	sync_env_to_list_conservative(char **env_array, t_cdllist *env_list)
{
	char			*key;
	char			*value;
	char			*equals_pos;
	t_cd_ll_node	*new_node;
	int				i;
	int				key_len;

	if (!env_array || !env_list)
		return (1);
	i = 0;
	while (env_array[i])
	{
		// Split KEY=VALUE
		equals_pos = ft_strchr(env_array[i], '=');
		if (!equals_pos)
		{
			// Variable without value (export VAR)
			key = ft_strdup(env_array[i]);
			value = ft_strdup("");
		}
		else
		{
			key_len = equals_pos - env_array[i];
			key = ft_substr(env_array[i], 0, key_len);
			value = ft_strdup(equals_pos + 1);
		}
		if (key && value)
		{
			// Simply add new node (don't check for duplicates for now)
			new_node = cdll_new_node(key, value, 0);
			if (new_node)
				cdll_add_back(env_list, new_node);
		}
		// Clean up our temporary copies
		free(key);
		free(value);
		i++;
	}
	return (0);
}

/**
 * @brief Main sync function - choose implementation
 */
int	sync_env_to_list(char **env_array, t_cdllist *env_list)
{
	// STEP 1: Use disabled version for testing
	return (sync_env_to_list_disabled(env_array, env_list));
	// STEP 2: Uncomment this to enable basic persistence
	// return (sync_env_to_list_conservative(env_array, env_list));
}

/**
 * @brief Wrapper function called from builtins
 */
void	sync_environment_changes(t_shell *shell)
{
	if (!shell || !shell->data || !shell->data->envp_copy || !shell->env)
		return ;

	if (sync_env_to_list(shell->env, shell->data->envp_copy) != 0)
	{
		// Handle sync error silently for now
		return ;
	}
}