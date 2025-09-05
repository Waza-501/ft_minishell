/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 11:54:17 by haile         #+#    #+#                 */
/*   Updated: 2025/09/05 11:55:01 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_atoi_check(const char *str, bool *check)
{
	int		i;
	int		sign;
	size_t	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - 48;
		if ((sign == 1 && res > LONG_MAX)
			|| (sign == -1 && res > (size_t) LONG_MAX + 1))
			*check = true;
	}
	if (i == 0 || str[i])
		*check = true;
	return (sign * res);
}

static void	exit_checker(char *str)
{
	bool	check;

	check = false;
	g_return_value = ft_atoi_check(str, &check);
	if (check)
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
		g_return_value = 2;
	}
}

int	ft_exit(t_cmds *cmd)
{
	if (!cmd)
	{
		ft_putstr_fd("exit\n", STDOUT);
		exit(g_return_value);
	}
	if (cmd->pid != 0)
		ft_putstr_fd("exit\n", STDOUT);
	if (!cmd->str[1])
		exit(g_return_value);
	if (cmd->str[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (1);
	}
	exit_checker(cmd->str[1]);
	exit(g_return_value);
}