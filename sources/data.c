/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 15:02:32 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/25 12:52:44 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

void	free_data(t_data *data)
{
	cdll_del_list(data->envp_copy);
	ft_free(&data->input);
	if (data->lexer)
		clear_lexer(data);
	if (data->commands)
		clear_commands(data);
	ft_free(&data);
}

/*wipe all data from data*/
int	reset_data(t_data *data, int code)
{
	ft_free(&data->input);
	if (data->lexer)
		clear_lexer(data);
	if (data->commands)
		clear_commands(data);
	data->exit_code = code;
	return (code);
}

t_data	*init_data(void)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->input = NULL;
	new->envp_copy = NULL;
	new->lexer = NULL;
	new->commands = NULL;
	new->exit_code = 0;
	return (new);
}
