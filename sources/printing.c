/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 11:12:51 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 14:44:51 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_list(t_commands *list)
{
	int			idx;
	int			i;
	t_commands	*copy;

	copy = list;
	i = 1;
	while (copy)
	{
		idx = 0;
		printf("node %i: [", i);
		if (copy->args)
		{
			while (copy->args[idx])
			{
				printf("%s", copy->args[idx]);
				idx++;
				if (copy->args[idx])
					printf(", ");
			}
		}
		printf("]");
		print_file_list(copy->infiles, "infiles");
		print_file_list(copy->outfiles, "outfiles");
		printf("\n");
		copy = copy->next;
		i++;
	}
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
