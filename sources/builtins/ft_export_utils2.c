/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_utils2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/17 10:00:43 by haile         #+#    #+#                 */
/*   Updated: 2025/11/17 13:10:11 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Handle invalid identifier case
 * @param str Invalid identifier
 * @return 1 (error occurred)
 */
static int	handle_invalid_identifier(t_shell *shell, char *str)
{
	export_err(shell, str);
	return (1);
}

/*
 * @brief Handle existing variable update
 * @param shell Shell structure
 * @param str Variable string
 * @return 1 (environment modified)
 */
static int	handle_existing_variable(t_shell *shell, char *str)
{
	(void)shell;
	(void)str;
	return (1);
}

/*
 * @brief Handle new variable assignment
 * @param shell Shell structure
 * @param str Variable string
 * @param identifier Type of identifier (1=normal, 2=append)
 * @return 1 if environment modified, 0 otherwise
 */
static int	handle_new_variable(t_shell *shell, char *str, int identifier)
{
	if (identifier == 2)
		join_arr(shell, str);
	else
		send_arr(shell, str);
	return (1);
}

/*
 * @brief Check and send environment variable
 * @param shell Shell structure
 * @param str Variable string to process
 * @return 1 if environment was modified, 0 if no changes made
 * Flow: Check if Invalid identifier
 */
int	check_and_send(t_shell *shell, char *str)
{
	int	identifier;

	identifier = check_identifier(str);
	if (!identifier)
		return (handle_invalid_identifier(shell, str));
	if (!check_validity(str))
		return (0);
	if (if_exist(shell->env, str))
		return (handle_existing_variable(shell, str));
	return (handle_new_variable(shell, str, identifier));
}

/*
 * @brief Check and send environment variable, tracking if changes were made
 * @param shell Shell structure
 * @param str Variable string to process
 * @return 1 if environment was modified, 0 if no changes made
 * Flow: Check if Invalid identifier
 */

// int	check_and_send(t_shell *shell, char *str)
// {
// 	int	check;
// 	int	identifier;
// 	int	env_modified;

// 	check = 0;
// 	identifier = check_identifier(str);
// 	env_modified = 0;
// 	if (!identifier)
// 	{
// 		check = export_err(str);
// 	}
// 	else if (!check_validity(str))
// 	{
// 		check = 1;
// 	}
// 	else if (if_exist(shell->env, str))
// 	{
// 		check = 1;
// 		env_modified = 1;
// 	}
// 	else
// 	{
// 		if (!check)
// 		{
// 			if (identifier == 2)
// 			{
// 				join_arr(shell, str);
// 				env_modified = 1;
// 			}
// 			else
// 			{
// 				send_arr(shell, str);
// 				env_modified = 1;
// 			}
// 		}
// 	}
// 	return (env_modified);
// }
