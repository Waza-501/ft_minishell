/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/31 09:49:10 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/06 13:15:48 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*new_lex_node(char *str)
{
	t_lexer		*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
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

t_lexer	*lex_last(t_lexer *list)
{
	t_lexer		*copy;

	copy = list;
	while (copy->next)
		copy = copy->next;
	return (copy);
}

void	lex_add_back(t_lexer **list, t_lexer *new)
{
	t_lexer	*end;

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

int	add_lex_node(char *str, t_lexer **lexer)
{
	int		dup_len;

	dup_len = 0;
	if (str[0] == S_Q)
	{
		lex_add_back(lexer, new_lex_node(strcpy_delim(str, S_Q, S_Q, S_Q)));
		// dup_len = ft_strlen_delim(str, S_Q);
		// printf("dup len is %i\n", dup_len);
		// dup_len = ft_strlen(lex_last(*lexer)->string);
		// printf("dup len is %i\n", dup_len);
	}
	else if (str[0] == D_Q)
	{
		lex_add_back(lexer, new_lex_node(strcpy_delim(str, D_Q, D_Q, D_Q)));
		// dup_len = ft_strlen_delim(str, D_Q);
		// printf("dup len is %i\n", dup_len);
		// dup_len = ft_strlen(lex_last(*lexer)->string);
		// printf("dup len is %i\n", dup_len);
	}
	else
	{
		lex_add_back(lexer, new_lex_node(strcpy_delim(str, SPACE, S_Q, D_Q)));
		// dup_len = ft_strlen_delim(str, SPACE);
		// printf("dup len is %i\n", dup_len);
		// dup_len = ft_strlen(lex_last(*lexer)->string);
		// printf("dup len is %i\n", dup_len);
	}
	dup_len = ft_strlen(lex_last(*lexer)->string);
	if (str[dup_len])
		if (str[dup_len] != ' ')
			lex_last(*lexer)->concat = true;
	return (dup_len);
}
