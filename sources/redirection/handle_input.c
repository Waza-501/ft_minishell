/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/03 16:08:57 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/05 15:19:52 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	close_heredoc(t_commands *list)
{
	if (close(list->infile))
	{
		ft_free(&list->infile_s);
		//list->hd = false;
		return (perror("minishell: "), 1);
	}
	if (unlink(list->infile_s))
		return (perror("minishell: "), 1);
	ft_free(&list->infile_s);
	//list->hd = false;
	return (0);
}

int	close_existing_fd_in(t_commands *list)
{
	if (list->infile == -1 || !list->infile_s)
		return (0);
	//if (list->hd == true)
	//{
	//	if (close_heredoc(list))
	//		return (1);
	//}
	//else
	//{
		ft_free(&list->infile_s);
		if (close(list->infile))
			return (perror("minishell: "), 1);
	//}
	list->infile = -1;
	return (0);
}

// bool	handle_input(t_data *data, t_commands *list, t_lexer *node)
// {
// 	if (close_existing_fd_in(list))
// 		return (false);
// 	list->infile_s = ft_strdup(node->string);
// 	if (!list->infile_s)
// 		malloc_error(data, true);
// 	list->infile = open(list->infile_s, O_RDONLY);
// 	if (list->infile == -1)
// 		return (perror("minishell: "), false);
// 	return (true);
// }


/*some things to consider:
	- if close fails, print error but continue. Bash does not care
	- don't free anything, just print the code and move on.*/
int	handle_input_new(t_files *list, int *fd)
{
	//if (close_existing_fd_in(list), &fd)
		//return (1);

	return (0);
}
