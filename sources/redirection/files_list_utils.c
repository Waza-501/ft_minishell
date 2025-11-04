/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 11:03:42 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 15:27:04 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

void	print_file_list(t_files *files, char *str)
{
	t_files	*copy;

	printf(" %s [", str);
	copy = files;
	if (copy)
	{
		while (copy)
		{
			printf("%s", copy->filename);
			if (copy->next)
				printf(", ");
			copy = copy->next;
		}
	}
	printf("]");
}
