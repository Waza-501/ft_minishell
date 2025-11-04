/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 11:29:41 by owen          #+#    #+#                 */
/*   Updated: 2025/11/04 16:28:36 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "parser.h"
#include "expand.h"

static int	finalize_list(t_data *data)
{
	t_lexer	*copy;
	int		idx;

	copy = data->lexer;
	idx = 0;
	while (copy)
	{
		if (copy->type > 3)
		{
			ft_free(&copy->string);
			if (merge_nodes(copy))
				malloc_error(data, false);
		}
		if (copy->type != HEREDOC && (copy->string[0] != '\''
				&& copy->string[ft_strlen(copy->string) - 1] != '\''))
		{
			if (remove_quotes(copy))
				malloc_error(data, false);
		}
		copy = copy->next;
	}
	return (0);
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
	if (concatenate_strings(data) == false)
		reset_data(data, 1);
	if (finalize_list(data))
		reset_data(data, 1);
	copy = data->lexer;
	print_tokenlist(copy);
	if (build_command_list(data))
		return (0);
	clear_lexer(data);
	print_command_list(data->commands);
	return (0);
}
