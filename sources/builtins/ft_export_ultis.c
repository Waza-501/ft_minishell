/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_ultis.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 11:58:34 by haile         #+#    #+#                 */
/*   Updated: 2025/11/04 15:00:23 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * TEMPORARY STUB: is_identifier
 * TODO: Implement proper identifier validation
 * Should check if character is valid for env var name (alphanumeric + underscore)
 */
int	is_identifier(char c)
{
	// Minimal implementation - allows alphanumeric and underscore
	return (ft_isalnum(c) || c == '_');
}

/*
 * TEMPORARY STUB: export_err
 * TODO: Implement proper error message printing
 * Should print "export: `str': not a valid identifier"
 */
int	export_err(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
	return (1);
}

/*
 * TEMPORARY STUB: check_validity
 * TODO: Implement full validation logic
 * Should check for proper format (NAME=VALUE or NAME+=VALUE)
 */
int	check_validity(char *str)
{
	int	i;

	i = 0;
	// Basic check: must have at least one character before '='
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


static int	check_identifier(char *str)
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

void	check_and_send(t_shell *shell, char *str)
{
	int	check;
	int	identifier;

	check = 0;
	identifier = check_identifier(str);
	if (!identifier)
		check = export_err(str);
	else if (!check_validity(str))
		check = 1;
	else if (if_exist(shell->env, str))
		check = 1;
	else
	{
		if (!check)
		{
			if (identifier == 2)
				join_arr(shell, str);
			else
				send_arr(shell, str);
		}
	}
}

