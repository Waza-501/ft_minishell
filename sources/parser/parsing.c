/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 11:29:41 by owen          #+#    #+#                 */
/*   Updated: 2025/11/17 13:15:46 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "parser.h"
#include "expand.h"

static int	finalize_list(t_data *data)
{
	t_lexer	*copy;
	t_lexer	*tmp;

	copy = data->lexer;
	while (copy)
	{
		if (is_space(copy->string) == true)
		{
			tmp = copy->next;
			lex_del_node(copy);
			copy = tmp;
		}
		else
		{
			if (copy->type > 3)
			{
				ft_free(&copy->string);
				merge_nodes(data, copy);
			}
			if (copy->type != HEREDOC)
				remove_quotes(data, copy);
			copy = copy->next;
		}
	}
	return (0);
}

int	parse_input(t_data *data, char *str)
{
	int	s_var;

	if (is_space(str))
		return (0);
	add_history(data->input);
	if (find_matching_quotes(str, false, false) == false)
		return (2);
	if (setup_lexer(data) == false)
		return (reset_data(data, 2));
	if (assign_type(data) == false)
		return (reset_data(data, 2));
	s_var = expand_args(data);
	if (s_var < 0)
		return (reset_data(data, 2));
	else if (s_var == 1)
		return (reset_data(data, 0));
	if (concatenate_strings(data) == false)
		reset_data(data, 1);
	if (finalize_list(data))
		reset_data(data, 1);
	if (build_command_list(data))
		return (0);
	clear_lexer(data);
	return (0);
}
