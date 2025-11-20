/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 11:03:42 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/20 09:55:47 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

int	outfile_open_error(t_files *file)
{
	ft_putstr_fd(MS_ERROR, STDERR_FILENO);
	ft_putstr_fd(file->filename, STDERR_FILENO);
	ft_putendl_fd(": permission denied", STDERR_FILENO);
	return (1);
}

int	infile_open_error(t_files *file)
{
	ft_putstr_fd(MS_ERROR, STDERR_FILENO);
	if (access(file->filename, F_OK))
	{
		ft_putstr_fd(file->filename, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else if (access(file->filename, R_OK))
	{
		ft_putstr_fd(file->filename, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	return (1);
}

void	print_remove_hd_error(char *str)
{
	ft_putstr_fd(MS_ERROR, STDERR_FILENO);
	ft_putstr_fd("Error: Failed to remove: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	print_close_fd_error(void)
{
	ft_putstr_fd(MS_ERROR, STDERR_FILENO);
	ft_putstr_fd("Error: Failed to close file descriptor ", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	delete_files_list(t_commands *cmd)
{
	t_files	*copy;
	t_files	*next;

	copy = cmd->infiles;
	while (copy)
	{
		next = copy->next;
		ft_free(&copy->filename);
		ft_free(&copy->hd_delim);
		ft_free(&copy);
		copy = next;
	}
	copy = cmd->outfiles;
	while (copy)
	{
		next = copy->next;
		ft_free(&copy->filename);
		ft_free(&copy);
		copy = next;
	}
}
