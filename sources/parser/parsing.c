/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 11:29:41 by owen          #+#    #+#                 */
/*   Updated: 2025/10/07 15:40:37 by owhearn       ########   odam.nl         */
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
	t_lexer		*copy;

	if (is_space(str))
		return (false);
	add_history(data->input);
	if (find_matching_quotes(str, false, false) == false)
		return (data->error = true, false);
	if (setup_lexer(data) == false)
		todo_exit(data);
	if (assign_type(data) == false)
		todo_exit(data);
	copy = data->lexer;
	if (expand_args(data) == false)
		todo_exit(data);
	copy = data->lexer;
	if (concatonate_strings(data->lexer) == false)
		todo_exit(data);
	copy = data->lexer;
	print_tokenlist(copy);
	if (build_command_list(data))
		return (false);
	clear_lexer(data);
	print_command_list(data->commands);
	clear_commands(data->commands);
	return (true);
}
