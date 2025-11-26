/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 11:29:41 by owen          #+#    #+#                 */
/*   Updated: 2025/11/26 09:32:20 by owhearn       ########   odam.nl         */
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

void	print_tokenlist(t_lexer *list)
{
	printf("-------------------------\n\n");
	while (list)
	{
		printf("Type: ");
		if (list->type == EMPTY)
			printf("[EMPTY][concatenate = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == ARG)
			printf("[ARG][concatenate = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == NOEXPAND)
			printf("[NOEXPAND][concatenate = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == PIPE)
			printf("[PIPE][concatenate = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == INPUT)
			printf("[INPUT][concatenate = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == OUTPUT)
			printf("[OUTPUT][concatenate = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == HEREDOC)
			printf("[HEREDOC][concatenate = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == APPEND)
			printf("[APPEND][concatenate = %i]: String [%s]\n", list->concat, list->string);
		list = list->next;
	}
	printf("-------------------------\n\n");
}

int	parse_input(t_data *data, char *str)
{
	int		s_var;
	t_lexer	*copy;

	printf("%i\n", data->input[0]);
	add_history(data->input);
	if (is_space(str))
		return (0);
	if (find_matching_quotes(str, false, false) == false)
		return (2);
	if (setup_lexer(data) == false)
		return (reset_data(data, 2));
	if (assign_type(data) == false)
		return (reset_data(data, 2));
	copy = data->lexer;
	print_tokenlist(copy);
	s_var = expand_args(data);
	if (s_var < 0)
		return (reset_data(data, 2));
	else if (s_var >= 1)
		return (reset_data(data, s_var));
	copy = data->lexer;
	print_tokenlist(copy);
	if (concatenate_strings(data) == false)
		reset_data(data, 1);
	copy = data->lexer;
	print_tokenlist(copy);
	if (finalize_list(data))
		reset_data(data, 1);
	if (build_command_list(data))
		return (0);
	clear_lexer(data);
	return (0);
}
