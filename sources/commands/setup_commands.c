/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:26:24 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/06 10:53:52 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

static int	add_arg_to_list(t_data *data, t_commands *list, t_lexer *node)
{
	char	**new_arr;
	int		idx;

	new_arr = NULL;
	idx = 0;
	while (list->args && list->args[idx])
		idx++;
	new_arr = malloc(sizeof(char *) * (idx + 2));
	if (!new_arr)
		malloc_error(data, true);
	idx = 0;
	while (list->args && list->args[idx])
	{
		new_arr[idx] = list->args[idx];
		idx++;
	}
	new_arr[idx] = ft_strdup(node->string);
	if (!new_arr[idx])
		return (ft_free(new_arr), malloc_error(data, true), 1);
	new_arr[idx + 1] = NULL;
	ft_free(&list->args);
	list->args = new_arr;
	return (0);
}

static int	add_arg_cmd(t_data *data, t_commands *list, t_lexer *node)
{
	if (node->type > 3)
		simplified_redir(data, list, node);
	else
		add_arg_to_list(data, list, node);
	return (0);
}

int	build_command_list(t_data *data)
{
	t_lexer		*copy;

	copy = data->lexer;
	if (add_command_node(&data->commands))
		return (1);
	while (copy)
	{
		if (copy->type == PIPE)
			add_command_node(&data->commands);
		else
			add_arg_cmd(data, command_list_last(data->commands), copy);
		copy = copy->next;
	}
	return (0);
}
