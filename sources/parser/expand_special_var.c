/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_special_var.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/17 12:25:44 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/25 12:45:42 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "parser.h"

static int	single_var(t_data *data, char *str, char *code, t_lexer	*node)
{
	ft_free(&str);
	ft_free(&node->string);
	node->string = code;
	if (is_quoted(data->lexer->string))
		remove_quotes(data, data->lexer);
	ft_putstr_fd(data->lexer->string, STDOUT_FILENO);
	ft_putendl_fd(": command not found", STDOUT_FILENO);
	data->exit_code = 127;
	return (127);
}

int	set_last_exit_code(t_data *data, char *str, t_lexer *node)
{
	char	*code;
	char	*end;
	bool	result;

	code = ft_itoa(data->exit_code);
	if (!node->prev && !node->next && ((ft_strlen(node->string) == 2)
			|| (ft_strlen(node->string) == 4 && is_quoted(node->string))))
		return (single_var(data, str, code, node));
	end = ft_strdup(&node->string[find_dollar_sign(node->string) + 2]);
	if (!code || !end)
	{
		ft_free(&str);
		ft_free(&code);
		ft_free(&end);
		malloc_error(data, true);
	}
	result = reform_string(node, str, end, code);
	ft_free(&str);
	ft_free(&code);
	ft_free(&end);
	if (result == false)
		malloc_error(data, false);
	return (0);
}
