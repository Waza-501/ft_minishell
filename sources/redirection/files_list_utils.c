/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 11:03:42 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 11:57:09 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_file_list(t_files *files, char *str)
{
	t_files	*copy;

	printf(" %s [", str);
	copy = files;
	if (copy)
	{
		while (copy)
		{
			//if (copy->filename)
				printf("%s", copy->filename);
			if (copy->next)
				printf(", ");
			copy = copy->next;
		}
	}
	printf("]");
}
