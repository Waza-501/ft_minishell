/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 11:29:41 by owen          #+#    #+#                 */
/*   Updated: 2025/08/26 09:04:41 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f');
}

bool	is_space(const char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!is_whitespace(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	parse_input(t_data *data, char *str)
{
	if (is_space(str))
		return (false);
	add_history(data->input);
	if (find_matching_quotes(str, false, false) == false)
		return (data->error = true, false);
	if (setup_lexer(data) == false)
		/*implement error handling function*/
		exit (1);
	if (assign_type(data) == false)
		/*implement error handling function*/
		exit(1);
	if (expand_args(data) == false)
		/*implement error handling function*/
		exit(1);	
	clear_lexer(data);
	return (true);
}
