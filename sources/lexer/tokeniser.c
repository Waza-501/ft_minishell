/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokeniser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 11:48:40 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/30 13:52:46 by owhearn       ########   odam.nl         */
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
		else
			list->type = INPUT;
	}
	else if (list->string[0] == '>')
	{
		if (list->string[1] && list->string[1] == '>')
			list->type = APPEND;
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

int	check_syntax(t_data *data)
{
	t_lexer	*copy;

	copy = data->lexer;
	while (copy)
	{
		if (copy->type > 2)
		{
			if (!copy->next)
			{
				print_syntax_error(SYNTAX, "newline");
				print_error(SYNTAX_EOF);
				return (1);
			}
			else if (copy->next->type > 2)
			{
				print_syntax_error(SYNTAX, copy->next->string);
				return (1);
			}
		}
		copy = copy->next;
	}
	return (0);
}

bool	assign_type(t_data *data)
{
	t_lexer	*copy;

	copy = data->lexer;
	while (copy)
	{
		identify_type(copy);
		copy = copy->next;
	}
	copy = data->lexer;
	if (check_syntax(data))
		return (false);
	return (true);
}
