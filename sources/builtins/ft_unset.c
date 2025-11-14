/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 12:00:55 by haile         #+#    #+#                 */
/*   Updated: 2025/11/14 08:58:19 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Copy environment array excluding specified variable
 * @param env Source environment array
 * @param rtn Destination array (pre-allocated)
 * @param str Variable name to exclude
 */
static void	unset_array(char **env, char **rtn, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) != 0)
		{
			rtn[j] = ft_strdup(env[i]);
			if (!rtn[j])
			{
				ft_free_arr(rtn);
				return ;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Check if variable exists in environment
 * @param str Variable name to search for
 * @param env Environment array
 * @return true if found, false otherwise
 */
static bool	in_env(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (env && env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0 && (env[i][len] == '='
				|| env[i][len] == '\0'))
			return (true);
		i++;
	}
	return (false);
}
/**
 * @brief Create new environment array with one variable removed
 * @param shell Shell structure
 * @param var_name Variable to remove
 * @return 0 on success, -1 on failure
 */
static int	remove_var_from_env(t_shell *shell, char *var_name)
{
	int		i;
	char	**rtn;

	i = 0;
	while (shell->env[i])
		i++;
	rtn = ft_calloc(i, sizeof(char *));
	if (!rtn)
		return (-1);
	unset_array(shell->env, rtn, var_name);
	ft_free_arr(shell->env);
	shell->env = rtn;
	return (0);
}

/**
 * @brief Unset environment variables
 * @param cmd Command structure
 * @param shell Shell state
 * @return 0 on success, -1 on error
 */
int	ft_unset(t_commands *cmd, t_shell *shell)
{
	int	j;

	j = 1;
	if (!cmd->args[1])
		return (0);
	while (cmd->args[j])
	{
		if (in_env(cmd->args[j], shell->env))
		{
			if (remove_var_from_env(shell, cmd->args[j]) != 0)
				return (-1);
		}
		j++;
	}
	return (0);
}
