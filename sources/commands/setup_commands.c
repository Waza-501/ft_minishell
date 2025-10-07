/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:26:24 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/07 15:48:40 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*add possible free + false return function*/
bool	set_redirect(t_commands	*list, t_lexer *node)
{
	if (node->type == INPUT)
	{
		if (handle_input(list, node) == false)
			return (false);
	}
	else if (node->type == OUTPUT)
	{
		if (handle_output(list, node) == false)
			return (false);
	}
	else if (node->type == APPEND)
	{
		if (handle_output(list, node) == false)
			return (false);
	}
	else if (node->type == HEREDOC)
	{
		if (handle_output(list, node) == false)
			return (false);
	}
	return (true);
}

int	add_arg_to_list(t_commands *list, t_lexer *node)
{
	char	**new_arr;
	int		idx;

	new_arr = NULL;
	idx = 0;
	while (list->args && list->args[idx])
		idx++;
	new_arr = malloc(sizeof(char *) * (idx + 2));
	if (!new_arr)
		return (1);
	idx = 0;
	while (list->args && list->args[idx])
	{
		new_arr[idx] = list->args[idx];
		idx++;
	}
	new_arr[idx] = ft_strdup(node->string);
	new_arr[idx + 1] = NULL;
	if (!new_arr[idx])
		return (free(new_arr), 1);
	free(list->args);
	list->args = new_arr;
	return (0);
}

/*fix this either later, or tomorrow*/
int	add_arg_cmd(t_commands *list, t_lexer *node)
{
	if (node->type > 3)
	{
		if (set_redirect(list, node) == false)
			return (1);
	}
	else
	{
		if (add_arg_to_list(list, node))
			return (1);
	}
	return (0);
}

int	check_commands(t_commands *list)
{
	(void)list;
	printf("to do: check commands\n");
	return (0);
}

/**
 * @brief Builds a linked list of command structures from lexer tokens.
 *
 * Parses the lexer token list, creating a new command node for each pipe token,
 * and adding arguments or redirections to the current command node for other
 * tokens. The resulting linked list represents the sequence of commands to be
 * executed, separated by pipes.
 *
 * @param data Pointer to the main data structure containing the lexer tokens.
 * @return int 0 on success, 1 on failure (e.g., memory allocation error).
 */
int	build_command_list(t_data *data)
{
	t_lexer		*copy;

	copy = data->lexer;
	if (add_command_node(&data->commands))
		return (1);
	while (copy)
	{
		if (copy->type == PIPE)
		{
			if (add_command_node(&data->commands))
				return (1);
		}
		else
		{
			if (add_arg_cmd(command_list_last(data->commands), copy))
				return (1);
		}
		copy = copy->next;
	}
	if (check_commands(data->commands))
		return (1);
	return (0);
}
