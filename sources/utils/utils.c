/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/29 14:10:30 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/22 11:33:59 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *ptr)
{
	void	**target;

	if (!ptr)
		return ;
	target = (void **)ptr;
	if (*target)
	{
		free(*target);
		*target = NULL;
	}
}

int	find_other_half(char *str, char delim, bool *delim_toggle)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] && str[idx] == delim)
		{
			*delim_toggle = false;
			return (idx + 1);
		}
		idx++;
	}
	return (idx);
}

bool	find_matching_quotes(char *str, bool s_q, bool d_q)
{
	int		idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == S_Q)
		{
			s_q = true;
			idx += find_other_half(&str[idx + 1], S_Q, &s_q);
		}
		else if (str[idx] == D_Q)
		{
			d_q = true;
			idx += find_other_half(&str[idx + 1], D_Q, &d_q);
		}
		idx++;
	}
	if (s_q == true)
		return (print_error(EOF_SQ), false);
	else if (d_q == true)
		return (print_error(EOF_DQ), false);
	return (true);
}
