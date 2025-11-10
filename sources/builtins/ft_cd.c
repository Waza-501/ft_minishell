/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:23:18 by haile         #+#    #+#                 */
/*   Updated: 2025/11/10 01:55:32 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h> // Add to includes

static void	update_pwd(char *pwd, t_shell *shell)
{
	if (pwd)
	{
		pwd = ft_strjoin_free_2nd_ARG("OLDPWD=", pwd);
		ft_export(0, shell, pwd);
		free(pwd);
	}
	pwd = ft_strjoin_free_2nd_ARG("PWD=", ft_getcwd());
	ft_export(0, shell, pwd);
	free(pwd);
}

static int	ft_chdir(char *path, t_shell *shell)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (!pwd && path[0] != '/')
	{
		perror("cd: error retrieving current directory: getcwd: cannot access\
 parent directories");
		return (0);
	}
	if (chdir(path) != 0)
	{
		perror(path);
		free(pwd);
		return (1);
	}
	update_pwd(pwd, shell);
	return (0);
}

static int	cd_minus(t_shell *shell)
{
	int	i;
	int	ret;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp("OLDPWD=", shell->env[i], 7) == 0)
			break ;
		i++;
	}
	if (!shell->env[i])
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR);
		return (1);
	}
	ret = ft_chdir(&shell->env[i][7], shell);
	if (ret == 0)
		ft_pwd();
	return (ret);
}

static int	cd_home(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp("HOME=", shell->env[i], 5) == 0)
			break ;
		i++;
	}
	if (!shell->env[i])
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR);
		return (1);
	}
	return (ft_chdir(&shell->env[i][5], shell));
}

int	ft_cd(t_commands *cmd, t_shell *shell)
{
	if (!cmd->args[1])
		return (cd_home(shell));
	else if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR);
		return (1);
	}
	else if (cmd->args[1][0] == '\0')
		return (0);
	else if (ft_strncmp("-", cmd->args[1], 2) == 0)
		return (cd_minus(shell));
	return (ft_chdir(cmd->args[1], shell));
}
