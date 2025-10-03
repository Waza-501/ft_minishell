/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 11:29:41 by owen          #+#    #+#                 */
/*   Updated: 2025/10/03 17:31:48 by owhearn       ########   odam.nl         */
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

bool	set_redirect(t_token *lexer, t_data *data)
{
	if (lexer->type == INPUT)
	{
		if (handle_input(lexer, data) == false)
			return (false);
	}
	else if (lexer->type == OUTPUT)
	{
		if (handle_output(lexer, data) == false)
			return (false);
	}
	else if (lexer->type == APPEND)
	{
		if (handle_output(lexer, data) == false)
			return (false);
	}
	else if (lexer->type == HEREDOC)
	{
		if (handle_output(lexer, data) == false)
			return (false);
	}
	return (true);
}

// bool	concatonate_redirect(t_data *data)
// {
// 	t_token		*copy;

// 	copy = data->lexer;
// 	if (concatonate_strings(copy))
// 		return (false);
// 	while (copy->next)
// 	{
// 		if (copy->type > 3)
// 			set_redirect(copy);
// 		copy = copy->next;
// 	}
// 	return (true);
// }

bool	parse_input(t_data *data, char *str)
{
	t_token		*copy;

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
	copy = data->lexer;
	if (expand_args(data) == false)
		/*implement error handling function*/
		exit(1);
	copy = data->lexer;
	if (concatonate_strings(data->lexer) == false)
		/*implement error handling function*/
		exit(1);
	copy = data->lexer;
	print_tokenlist(copy);
	build_command_list(data);
	clear_lexer(data);
	return (true);
}
