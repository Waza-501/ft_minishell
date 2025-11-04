/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:26:24 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 09:03:44 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	simplified_redir(t_data *data, t_commands *list, t_lexer *node)
{
	if (node->type == INPUT || node->type == HEREDOC)
	{
		if (add_file_node(&list->infiles, node))
			malloc_error(data, false);
	}
	// {
	// 	ft_free(&list->infile_s);
	// 	if (node->type == INPUT)
	// 		list->infile_s = ft_strjoin("<", node->string);
	// 	else
	// 		list->infile_s = ft_strjoin("<<", node->string);
	// }
	else if (node->type == OUTPUT || node->type == APPEND)
	{
		if (add_file_node(&list->outfiles, node))
			malloc_error(data, false);
	}
	// {
	// 	ft_free(&list->outfile_s);
	// 	if (node->type == OUTPUT)
	// 	if (node->type == APPEND)
	// 		list->outfile_s = ft_strjoin(">>", node->string);
	// }
	return (true);
}

/*nope. It's easier to handle things like that later on*/
bool	set_redirect(t_data *data, t_commands	*list, t_lexer *node)
{
	return (simplified_redir(data, list, node));
	if (node->type == INPUT)
		return (handle_input(data, list, node));
	else if (node->type == OUTPUT)
		return (handle_output(data, list, node));
	else if (node->type == APPEND)
		return (handle_output(data, list, node));
	else if (node->type == HEREDOC)
		return (handle_output(data, list, node));
}

int	add_arg_to_list(t_data *data, t_commands *list, t_lexer *node)
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

/*fix this either later, or tomorrow*/
int	add_arg_cmd(t_data *data, t_commands *list, t_lexer *node)
{
	if (node->type > 3)
	{

		if (set_redirect(data, list, node) == false)
			return (1);
	}
	else
	{
		if (add_arg_to_list(data, list, node))
			return (1);
	}
	return (0);
}

int	check_commands(t_commands *list)
{
	(void)list;
	printf("to do: check commands. Make sure they don't end on a pipe\n");
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
			if (add_arg_cmd(data, command_list_last(data->commands), copy))
				return (1);
		}
		copy = copy->next;
	}
	if (check_commands(data->commands))
		return (1);
	return (0);
}
