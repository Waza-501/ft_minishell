/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 11:12:51 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/13 13:23:21 by owhearn       ########   odam.nl         */
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

void	print_envp(char **envp, t_cdllist *list)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	i = 0;
	while (i < list->size)
	{
		printf("%s = %s\n", list->current->var_1, list->current->var_2);
		list->current = list->current->next;
		i++;
	}
	list->current = list->head;
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
