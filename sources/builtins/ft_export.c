/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 14:02:47 by haile         #+#    #+#                 */
/*   Updated: 2025/11/17 13:08:04 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_exist(char **env, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len] != '=')
		len++;
	if (!env)
		return (0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len))
		{
			free(env[i]);
			env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**new_array(char **env, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		rtn[i] = ft_strdup(env[i]);
		i++;
	}
	rtn[i] = ft_strdup(str);
	rtn[i + 1] = NULL;
	return (rtn);
}

int	send_arr(t_shell *shell, char *str)
{
	int		i;
	char	**rtn;

	i = 0;
	while (shell->env && shell->env[i])
		i++;
	rtn = ft_malloc((i + 2) * sizeof(char *));
	if (!rtn)
		return (0);
	new_array(shell->env, rtn, str);
	ft_free_arr(shell->env);
	shell->env = rtn;
	return (1);
}

/*
 * @brief Handle export display mode (no arguments)
 * @param shell Shell instance with environment
 * @return 0 on success, 1 on error
 */
static int	handle_export_display(t_shell *shell)
{
	char	**sorted;

	sorted = sort_env(shell->env);
	if (!sorted)
	{
		shell->data->exit_code = 1;
		return (1);
	}
	print_env(sorted);
	free_sorted_env(sorted);
	return (0);
}
/**
 * @brief Export builtin command implementation
 * @param cmd Command structure (NULL for direct string mode)
 * @param shell Shell instance with environment
 * @param str Direct string parameter (NULL for cmd args mode)
 * @return Exit code (0 success, 1 error)
 * Display sorted environment (!str && !cmd->args[1])
 * Handle single string parameter (str provided)
 * Handle command arguments (cmd->args[1+] provided)
 */

int	ft_export(t_commands *cmd, t_shell *shell, char *str)
{
	int		i;

	shell->data->exit_code = 0;
	if (!str && !cmd->args[1])
		return (handle_export_display(shell));
	if (str)
	{
		if (!if_exist(shell->env, str))
			send_arr(shell, str);
	}
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			check_and_send(shell, cmd->args[i]);
			i++;
		}
	}
	return (shell->data->exit_code);
}
