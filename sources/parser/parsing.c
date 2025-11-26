/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 11:29:41 by owen          #+#    #+#                 */
/*   Updated: 2025/11/26 11:31:21 by owhearn       ########   odam.nl         */
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
			lex_del_node(data, copy);
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

static int	ft_add_history(t_data *data)
{
	if (data->input[0] == 0 || data->input[0] == 31)
		return (1);
	add_history(data->input);
	if (is_space(data->input))
		return (1);
	return (0);
}

int	parse_input(t_data *data, char *str)
{
	int		s_var;

	if (ft_add_history(data))
		return (0);
	if (find_matching_quotes(str, false, false) == false)
		return (2);
	if (setup_lexer(data) == false)
		return (reset_data(data, 2));
	if (assign_type(data) == false)
		return (reset_data(data, 2));
	s_var = expand_args(data);
	if (s_var < 0)
		return (reset_data(data, 2));
	else if (s_var >= 1)
		return (reset_data(data, s_var));
	if (concatenate_strings(data) == false)
		reset_data(data, 1);
	if (finalize_list(data))
		reset_data(data, 1);
	if (build_command_list(data))
		return (0);
	clear_lexer(data);
	return (0);
}
