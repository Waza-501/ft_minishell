/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokeniser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 11:48:40 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/28 06:22:13 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	identify_type(t_token *list)
{
	if (list->string[0] == '\'')
		list->type = NOEXPAND;
	else if (list->string[0] == '|')
		list->type = PIPE;
	else if (list->string[0] == '<')
	{
		if (list->string[1] && list->string[1] == '<')
			list->type = HEREDOC;
		else if (list->string[1])
			return (printf("unexpected eof\n"), 1);
		else
			list->type = INPUT;
	}
	else if (list->string[0] == '>')
	{
		if (list->string[1] && list->string[1] == '>')
			list->type = APPEND;
		else if (list->string[1])
			return (printf("unexpected eof\n"), 1);
		else
			list->type = OUTPUT;
	}
	else
		list->type = ARG;
	return (0);
}

void	print_tokenlist(t_token *list)
{
	printf("-------------------------\n\n");
	while (list)
	{
		printf("Type: ");
		if (list->type == EMPTY)
			printf("[EMPTY]-String [%s]\n", list->string);
		else if (list->type == ARG)
			printf("[ARG]-String [%s]\n", list->string);
		else if (list->type == NOEXPAND)
			printf("[NOEXPAND]-String [%s]\n", list->string);
		else if (list->type == PIPE)
			printf("[PIPE]-String [%s]\n", list->string);
		else if (list->type == INPUT)
			printf("[INPUT]-String [%s]\n", list->string);
		else if (list->type == OUTPUT)
			printf("[OUTPUT]-String [%s]\n", list->string);
		else if (list->type == HEREDOC)
			printf("[HEREDOC]-String [%s]\n", list->string);
		else if (list->type == APPEND)
			printf("[APPEND]-String [%s]\n", list->string);
		list = list->next;
	}
	printf("-------------------------\n\n");
}

bool	assign_type(t_data *data)
{
	t_token	*copy;

	copy = data->lexer;
	while (copy)
	{
		if (identify_type(copy))
			exit(1);
		copy = copy->next;
	}
	copy = data->lexer;
	print_tokenlist(copy);
	return (true);
}
