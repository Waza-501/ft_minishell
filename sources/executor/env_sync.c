/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_sync.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 10:51:54 by haile         #+#    #+#                 */
/*   Updated: 2025/11/14 11:08:21 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parse KEY=VALUE string into separate components
 * @param env_string String in format "KEY=VALUE"
 * @param key Output for key part (caller must free)
 * @param value Output for value part (caller must free)
 * @return 0 on success, 1 on failure
 */
static int	split_env_string(const char *env_string, char **key, char **value)
{
	char	*equals_pos;
	int		key_len;

	if (!env_string || !key || !value)
		return (1);
	equals_pos = ft_strchr(env_string, '=');
	if (!equals_pos)
	{
		*key = ft_strdup(env_string);
		*value = ft_strdup("");
	}
	else
	{
		key_len = equals_pos - env_string;
		*key = ft_substr(env_string, 0, key_len);
		*value = ft_strdup(equals_pos + 1);
	}
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		return (1);
	}
	return (0);
}
/**
 * @brief Update single environment variable using existing cdll functions
 * @param env_list The environment linked list
 * @param env_string String in format "KEY=VALUE"
 * @return 0 on success, 1 on failure
 * Check if the node already exists BEFORE updating
 * If it was an update, cdll_update_list leaked the key. Free it
 * If it was a new node, the list took ownership of both key and value
 */
static int	update_single_var(t_cdllist *env_list, const char *env_string)
{
	char			*key;
	char			*value;
	char			*input[2];
	int				result;
	t_cd_ll_node	*existing_node;

	if (split_env_string(env_string, &key, &value) != 0)
		return (1);
	existing_node = cdll_get_node(env_list, false, key);
	input[0] = key;
	input[1] = value;
	result = cdll_update_list(env_list, input);
	if (existing_node)
		free(key);
	return (result);
}
/**
 * @brief Sync environment array back to linked list
 * @param env_array The shell's environment array
 * @param env_list The persistent environment linked list
 * @return 0 on success, 1 on failure
 *
 * Uses existing cdll_update_list function for safety
 */
int	sync_env_to_list(char **env_array, t_cdllist *env_list)
{
	int	i;
	int	errors;

	if (!env_array || !env_list)
		return (1);
	errors = 0;
	i = 0;
	while (env_array[i])
	{
		if (update_single_var(env_list, env_array[i]) != 0)
			errors++;
		i++;
	}
	if (errors > 0)
		return (1);
	else
		return (0);
}
/**
 * @brief Wrapper function called from cleanup_shell()
 * @param shell Shell structure containing environment and data pointer
 */
void	sync_environment_changes(t_shell *shell)
{
	if (!shell || !shell->data || !shell->data->envp_copy || !shell->env)
		return ;
	if (sync_env_to_list(shell->env, shell->data->envp_copy) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd("Warning: Failed to sync environment changes",
			STDERR_FILENO);
	}
	return ;
}
