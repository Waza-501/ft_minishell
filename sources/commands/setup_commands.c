/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:26:24 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/06 16:51:27 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


/*fix this either later, or tomorrow*/
int	add_arg_cmd(t_commands *list, t_lexer *node)
{
	if (node->type > 3)
		set_redirect(list, node);
	else

	return (0);
}

/**
 * @brief Builds a linked list of command structures from the lexer tokens.
 *
 * Iterates through the lexer token list, creating a new command node
 * for each pipe token and adding arguments or redirections to the current
 * command node for other tokens. The resulting linked list represents the
 * sequence of commands to be executed,
 * separated by pipes.
 *
 * @param data Pointer to the main data structure containing the lexer tokens.
 * @return int Returns 0 on success, 
 * 1 on failure (e.g., memory allocation error).
 */
int	build_command_list(t_data *data)
{
	t_lexer		*copy;
	t_commands	*list;

	copy = data->lexer;
	list = NULL;
	if (add_command_node(&list))
		return (1);
	while (copy)
	{
		if (copy->type == PIPE)
		{
			if (add_command_node(&list))
				return (1);
		}
		else
		{
			if (add_new_cmd(command_list_last(list), copy))
				return (1);
		}
		copy = copy->next;
	}
	return (0);
}
