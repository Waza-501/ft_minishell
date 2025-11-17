/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 11:58:34 by haile         #+#    #+#                 */
/*   Updated: 2025/11/17 13:09:03 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Check if character is valid for env var name
 * @param c Character to check
 * @return 1 if valid identifier character, 0 otherwise
 */
int	is_identifier(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
 * @brief Print export error message for invalid identifier
 * @param str Invalid identifier string
 * @return 1 (error code)
 */
int	export_err(t_shell *shell, char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell->data->exit_code = 1;
	return (1);
}

/*
 * @brief Check for proper format (NAME=VALUE or NAME+=VALUE)
 * @param str String to validate
 * @return 1 if valid format, 0 otherwise
 * Step:
 * 1. Basic check: must have at least one character before '='
 */
int	check_validity(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!is_identifier(str[i]) && !(str[i] == '+' && str[i + 1] == '='))
			return (0);
		i++;
	}
	return (1);
}
/*
 * @brief Check if identifier is valid (not starting with digit)
 * @param str String to check
 * @return 1 if valid, 2 if append operation, 0 if invalid
 */

int	check_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	if (str[i] == '=')
		return (0);
	while (str[i] != '=' && str[i])
	{
		if (!is_identifier(str[i]))
		{
			if (str[i] == '+' && str[i + 1] == '=' && i > 0)
				return (2);
			else
				return (0);
		}
		i++;
	}
	return (1);
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
		if (!ft_strncmp(shell->env[i], str, j - 1) && shell->env[i][j
			- 1] == '=')
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
