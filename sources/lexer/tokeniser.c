/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokeniser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 11:48:40 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/06 11:29:00 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	identify_type(t_lexer *list)
{
	if (list->string[0] == '\'')
		list->type = NOEXPAND;
	else if (list->string[0] == '|')
		list->type = PIPE;
	else if (list->string[0] == '<')
	{
		if (list->string[1] && list->string[1] == '<')
			list->type = HEREDOC;
		// else if (list->string[1])
		// 	return (printf("unexpected eof\n"), 1);
		else
			list->type = INPUT;
	}
	else if (list->string[0] == '>')
	{
		if (list->string[1] && list->string[1] == '>')
			list->type = APPEND;
		// else if (list->string[1])
		// 	return (printf("unexpected eof\n"), 1);
		else
			list->type = OUTPUT;
	}
	else
		list->type = ARG;
	return (0);
}

void	print_tokenlist(t_lexer *list)
{
	printf("-------------------------\n\n");
	while (list)
	{
		printf("Type: ");
		if (list->type == EMPTY)
			printf("[EMPTY][CONCATONATE = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == ARG)
			printf("[ARG][CONCATONATE = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == NOEXPAND)
			printf("[NOEXPAND][CONCATONATE = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == PIPE)
			printf("[PIPE][CONCATONATE = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == INPUT)
			printf("[INPUT][CONCATONATE = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == OUTPUT)
			printf("[OUTPUT][CONCATONATE = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == HEREDOC)
			printf("[HEREDOC][CONCATONATE = %i]: String [%s]\n", list->concat, list->string);
		else if (list->type == APPEND)
			printf("[APPEND][CONCATONATE = %i]: String [%s]\n", list->concat, list->string);
		list = list->next;
	}
	printf("-------------------------\n\n");
}

bool	assign_type(t_data *data)
{
	t_lexer	*copy;

	copy = data->lexer;
	while (copy)
	{
		if (identify_type(copy))
			exit(1);
		copy = copy->next;
	}
	copy = data->lexer;
	return (true);
}
