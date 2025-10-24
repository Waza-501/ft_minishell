/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/31 09:49:10 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/24 15:21:34 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*new_lex_node(char *str)
{
	t_lexer		*new;

	if (!str)
		return (NULL);
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
	{
		ft_free(str);
		return (malloc_error(NULL, true));
	}
	new->id = 0;
	new->type = EMPTY;
	new->string = str;
	new->concat = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*lex_last(t_lexer *list)
{
	t_lexer		*copy;

	copy = list;
	while (copy && copy->next)
		copy = copy->next;
	return (copy);
}

int	lex_add_next(t_lexer *list, t_lexer *new)
{
	t_lexer	*old_next;

	if (!new)
		return (1);
	old_next = list->next;
	list->next = new;
	new->next = old_next;
	new->prev = list;
	if (old_next)
		old_next->prev = new;
	return (0);
}

int	lex_add_back(t_lexer **list, t_lexer *new)
{
	t_lexer	*end;

	if (!*list)
	{
		if (!new)
			return (1);
		*list = new;
		return (0);
	}
	if (!new)
		return (1);
	end = lex_last(*list);
	end->next = new;
	new->prev = end;
	new->id = end->id + 1;
	return (0);
}

int	add_lex_node(char *str, t_lexer **lexer)
{
	int		dup_len;

	dup_len = 0;
	if (str[0] == S_Q)
	{
		if (lex_add_back(lexer, new_lex_node(strcpy_delim(str, S_Q, S_Q, S_Q))))
			return (-1);
	}
	else if (str[0] == D_Q)
	{
		if (lex_add_back(lexer, new_lex_node(strcpy_delim(str, D_Q, D_Q, D_Q))))
			return (-1);
	}
	else
	{
		if (lex_add_back(lexer, new_lex_node(
					strcpy_delim(str, SPACE, S_Q, D_Q))))
			return (-1);
	}
	dup_len = ft_strlen(lex_last(*lexer)->string);
	if (str[dup_len])
		if (str[dup_len] != ' ')
			lex_last(*lexer)->concat = true;
	return (dup_len);
}
