/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_print.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 15:53:56 by haile         #+#    #+#                 */
/*   Updated: 2025/11/17 09:55:34 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Print variable name (the part before '=')
 * @param str Environment variable string (format: "NAME=value")
 */
static void	print_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
}

/*
 * @brief Print variable value with quotes (the part after '=')
 * @param str Environment variable string (format: "NAME=value")
 * Steps:
 * 1. Prints: ="value". Find the '=' sign
 * 2. If no '=' found, prints nothing (variable declared but not set)
 * 3. Print ="value"
 * 4. TODO: Handle special characters that need escaping
 * For now, just print as-is
 */
static void	print_var_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return ;
	ft_putstr_fd("=\"", 1);
	i++;
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	ft_putchar_fd('"', 1);
}

/*
 * @brief Print a single environment variable in bash export format
 * @param env_var Single environment variable string
 *
 * Format: declare -x NAME="value"
 * Example: declare -x PATH="/usr/bin:/bin"
 */
static void	print_export_line(char *env_var)
{
	ft_putstr_fd("declare -x ", 1);
	print_var_name(env_var);
	print_var_value(env_var);
	ft_putchar_fd('\n', 1);
}

/*
 * @brief Print all environment variables in bash export format
 * @param sorted_env Sorted environment array
 *
 * Prints each variable in format:
 *   declare -x VAR="value"
 *
 * This matches bash's export output when called with no arguments
 */
void	print_env(char **sorted_env)
{
	int	i;

	if (!sorted_env)
		return ;
	i = 0;
	while (sorted_env[i])
	{
		print_export_line(sorted_env[i]);
		i++;
	}
}

/*
 * @brief Free a sorted environment array
 * @param sorted_env Array to free
 *
 * Helper function to free the sorted copy after printing
 */
void	free_sorted_env(char **sorted_env)
{
	int	i;

	if (!sorted_env)
		return ;
	i = 0;
	while (sorted_env[i])
	{
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}
