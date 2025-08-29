/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_strategy.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/29 12:24:27 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/29 12:38:36 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_structs(t_data *data)
{
	cdll_del_list(data->envp_copy);
	clear_lexer(data);
	free(data->input);
}
