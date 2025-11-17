/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 11:54:17 by haile         #+#    #+#                 */
/*   Updated: 2025/11/17 13:46:39 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
		if ((sign == 1 && res > LONG_MAX) || (sign == -1
				&& res > (size_t)LONG_MAX + 1))
			*check = true;
	}
	if (i == 0 || str[i])
		*check = true;
	return (sign * res);
}

static void	exit_checker(t_data *data, char *str)
{
	bool	check;

	check = false;
	data->exit_code = ft_atoi_check(str, &check);
	if (check)
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
		data->exit_code = 2;
	}
}

static void	exit_minishell(t_data *data, t_shell *shell, int fd_0, int fd_1)
{
	int	exit_code;

	exit_code = data->exit_code;
	cleanup_shell(shell);
	free_data(data);
	if (fd_0 != -1)
		close(fd_0);
	if (fd_1 != -1)
		close(fd_1);
	ft_putstr_fd("exit\n", STDOUT);
	exit (exit_code);
}
/**
 * Keep this just in case, after checking cmd exit
	// if (cmd->pid != 0)
	// 	ft_putstr_fd("exit\n", STDOUT);
 */

int	ft_exit(t_shell *shell, t_commands *cmd, int fd_0, int fd_1)
{
	t_data	*data;

	data = shell->data;
	if (!cmd)
	{
		ft_putstr_fd("exit\n", STDOUT);
		exit_minishell(data, shell, fd_0, fd_1);
	}
	if (!cmd->args[1])
		exit_minishell(data, shell, fd_0, fd_1);
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (1);
	}
	exit_checker(data, cmd->args[1]);
	exit_minishell(data, shell, fd_0, fd_1);
	return (0);
}
