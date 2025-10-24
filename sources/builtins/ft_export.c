/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 14:02:47 by haile         #+#    #+#                 */
/*   Updated: 2025/10/24 09:53:13 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

void	join_arr(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*new_var;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], str, j - 1)
			&& shell->env[i][j - 1] == '=')
		{
			shell->env[i] = ft_strjoin_free(shell->env[i], &str[j + 1]);
			return ;
		}
		i++;
	}
	new_var = ft_substr(str, 0, j - 1);
	new_var = ft_strjoin_free(new_var, &str[j]);
	ft_export(NULL, shell, new_var);
	free(new_var);
}

char **new_array(char **env, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		rtn[i] = env[i];
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
	new_arr(shell->env, rtn, str);
	free(shell->env);
	shell->env = rtn;
	return (1);
}

int	ft_export(t_commands *cmd, t_shell *shell, char *str)
{
	int		i;

	i = 1;
	g_exit_code = 0;
	if (!str && !cmd->args[1])
	{
		sort_env(shell);
		print_env(shell->sorted_env);
		return (0);
	}
	if (str)
	{
		if (!if_exist(shell->env, str))
			send_arr(shell, str);
	}
	else
	{
		while (cmd->args[i])
		{
			check_and_send(shell, cmd->args[i]);
			i++;
		}
	}
	return (g_exit_code);
}