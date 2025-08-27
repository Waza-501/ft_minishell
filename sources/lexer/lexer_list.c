/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/31 09:49:10 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/25 15:06:11 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_lexer(t_data *data)
{
	t_token	*start;

	start = data->lexer;
	while (data->lexer != NULL)
	{
		start = data->lexer->next;
		free(data->lexer->string);
		free(data->lexer);
		data->lexer = start;
	}
}

t_token	*new_lex_node(char *str)
{
	t_token		*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->id = 0;
	new->type = EMPTY;
	new->string = str;
	new->concat = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*lex_last(t_token *list)
{
	t_token		*copy;

	copy = list;
	while (copy->next)
		copy = copy->next;
	return (copy);
}

void	lex_add_back(t_token **list, t_token *new)
{
	t_token	*end;

	if (!*list)
	{
		*list = new;
		return ;
	}
	end = lex_last(*list);
	end->next = new;
	new->prev = end;
	new->id = end->id + 1;
}

int	add_lex_node(char *str, t_token **lexer)
{
	int	dup_len;
	int	idx;

	dup_len = 0;
	idx = 0;
	if (str[idx] == S_Q)
	{
		lex_add_back(lexer, new_lex_node(strcpy_delim(str, S_Q)));
		dup_len = ft_strlen_delim(str, S_Q);
	}
	else if (str[idx] == D_Q)
	{
		lex_add_back(lexer, new_lex_node(strcpy_delim(str, D_Q)));
		dup_len = ft_strlen_delim(str, D_Q);
	}
	else
	{
		lex_add_back(lexer, new_lex_node(strcpy_delim(str, SPACE)));
		dup_len = ft_strlen_delim(str, SPACE);
	}
	return (dup_len);
}
