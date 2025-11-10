/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 12:18:08 by haile         #+#    #+#                 */
/*   Updated: 2025/11/10 12:22:45 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize shell with full environment ownership
 * REPLACES any existing init_shell function
 */
t_shell	*init_shell(t_data *data)
{
	t_shell	*shell;

	shell = ft_malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = convert_cdll_to_env_array(data->envp_copy);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->cmds = NULL;
	shell->stop = false;
	shell->sorted_env = NULL;
	shell->sorted_env_valid = false;
	shell->data = data;
	return (shell);
}

/**
 * @brief Clean up shell (called at program exit)
 * REPLACES any existing cleanup_shell function
 */
void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		ft_free_arr(shell->env);
	if (shell->sorted_env)
		ft_free_arr(shell->sorted_env);
	free(shell);
}

/**
 * @brief Mark sorted environment as invalid (needs regeneration)
 */
void	invalidate_sorted_env(t_shell *shell)
{
	if (!shell)
		return ;
	shell->sorted_env_valid = false;
}

/**
 * @brief Get sorted environment (lazy generation)
 */
char	**get_sorted_env(t_shell *shell)
{
	if (!shell)
		return (NULL);
	if (shell->sorted_env_valid && shell->sorted_env)
		return (shell->sorted_env);
	if (shell->sorted_env)
		ft_free_arr(shell->sorted_env);
	shell->sorted_env = sort_env(shell->env);
	shell->sorted_env_valid = true;
	return (shell->sorted_env);
}

/**
 * @brief Export function for shell
 * REPLACES existing ft_export
 */
int	shell_export(t_shell *shell, char **args)
{
	char	**sorted;
	char	*str;
	int		count;
	char	**new_env;
	int		i;

	if (!shell)
		return (1);
	if (!args[1])
	{
		sorted = get_sorted_env(shell);
		if (!sorted)
		{
			g_exit_code = 1;
			return (1);
		}
		print_env(sorted);
		return (0);
	}
	str = args[1];
	if (!if_exist(shell->env, str))
	{
		count = 0;
		while (shell->env[count])
			count++;
		new_env = ft_malloc((count + 2) * sizeof(char *));
		if (!new_env)
		{
			g_exit_code = 1;
			return (1);
		}
		i = -1;
		while (++i < count)
			new_env[i] = ft_strdup(shell->env[i]);
		new_env[count] = ft_strdup(str);
		new_env[count + 1] = NULL;
		ft_free_arr(shell->env);
		shell->env = new_env;
	}
	invalidate_sorted_env(shell);
	g_exit_code = 0;
	return (0);
}

/**
 * @brief Unset environment variable in shell
 */
int	shell_unset(t_shell *shell, char *name)
{
	int		count;
	int		found;
	int		name_len;
	char	**new_env;
	int		j;
	int		i;

	if (!shell || !name)
		return (1);
	count = 0;
	found = -1;
	name_len = ft_strlen(name);
	while (shell->env[count])
	{
		if (ft_strncmp(shell->env[count], name, name_len) == 0
			&& shell->env[count][name_len] == '=')
		{
			found = count;
		}
		count++;
	}
	if (found == -1)
		return (0);
	new_env = ft_malloc(count * sizeof(char *));
	if (!new_env)
		return (1);
	j = 0;
	i = -1;
	while (++i < count)
	{
		if (i != found)
		{
			new_env[j] = ft_strdup(shell->env[i]);
			j++;
		}
	}
	new_env[j] = NULL;
	ft_free_arr(shell->env);
	shell->env = new_env;
	invalidate_sorted_env(shell);
	return (0);
}

/**
 * @brief Set environment variable in shell
 */
int	shell_setenv(t_shell *shell, char *name, char *value)
{
	char	*temp;
	char	*env_str;
	int		count;
	char	**new_env;
	int		i;

	if (!shell || !name || !value)
		return (1);
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (1);
	env_str = ft_strjoin(temp, value);
	if (!env_str)
		return (1);
	free(temp);
	if (!if_exist(shell->env, env_str))
	{
		count = 0;
		while (shell->env[count])
			count++;
		new_env = ft_malloc((count + 2) * sizeof(char *));
		if (!new_env)
		{
			free(env_str);
			return (1);
		}
		i = -1;
		while (++i < count)
			new_env[i] = ft_strdup(shell->env[i]);
		new_env[count] = ft_strdup(env_str);
		new_env[count + 1] = NULL;
		ft_free_arr(shell->env);
		shell->env = new_env;
	}
	free(env_str);
	invalidate_sorted_env(shell);
	return (0);
}
