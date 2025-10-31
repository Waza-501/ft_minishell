/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 11:29:41 by owen          #+#    #+#                 */
/*   Updated: 2025/10/31 13:06:11 by owhearn       ########   odam.nl         */
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

/*damn :( this needs fixing*/
int	parse_input(t_data *data, char *str)
{
	t_lexer		*copy;

	if (is_space(str))
		return (0);
	add_history(data->input);
	if (find_matching_quotes(str, false, false) == false)
		return (0);
	if (setup_lexer(data) == false)
		return (reset_data(data, 2));
	if (assign_type(data) == false)
		return (reset_data(data, 2));
	if (expand_args(data) == false)
		return (reset_data(data, 2));
	if (concatonate_strings(data) == false)
		reset_data(data, 1);
	copy = data->lexer;
	print_tokenlist(copy);
	if (build_command_list(data))
		return (0);/*implement error logging*/
	clear_lexer(data);
	print_command_list(data->commands);
	return (0);
}
