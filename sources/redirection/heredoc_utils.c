/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/06 12:46:29 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/06 16:05:02 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

char	*get_hd_filename(void)
{
	char		*filename;
	char		*filenumber;
	static int	i = 0;

	filename = NULL;
	filenumber = ft_itoa(i++);
	if (!filenumber)
		return (malloc_error(NULL, true));
	filename = ft_strjoin("/tmp/heredoc_", filenumber);
	ft_free(&filenumber);
	if (!filename)
		malloc_error(NULL, true);
	return (filename);
}
