/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_ultis.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 11:58:34 by haile         #+#    #+#                 */
/*   Updated: 2025/10/24 09:34:22 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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