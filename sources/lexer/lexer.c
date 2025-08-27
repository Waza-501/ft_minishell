/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 20:28:55 by owen          #+#    #+#                 */
/*   Updated: 2025/08/25 15:09:47 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_delim(char *str, char delim)
{
	size_t	size;

	size = 0;
	if (delim == S_Q || delim == D_Q)
		size++;
	while (str[size] && str[size] != delim)
		size++;
	if (delim == SPACE)
		return (size);
	//printf("size until delim:-%zu\n", size);
	return (size + 1);
}

char	*strcpy_delim(char *str, char delim)
{
	size_t	idx;
	size_t	size;
	char	*new;

	idx = 0;
	size = ft_strlen_delim(str, delim);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (idx < size)
	{
		new[idx] = str[idx];
		idx++;
	}
	new[idx] = '\0';
	return (new);
}

bool	id_token(char *str)
{
	int		idx;

	idx = 0;
	if (str[idx] == '|')
		return (true);
	else if (str[idx] == '<')
		return (true);
	else if (str[idx] == '>')
		return (true);
	return (false);
}

/*temp function*/
void	print_lex(t_data *data)
{
	t_token		*start;

	start = data->lexer;
	while (start->next)
	{
		printf("%s\n", start->string);
		start = start->next;
	}
	printf("%s\n", start->string);
}

bool	setup_lexer(t_data *data)
{
	char	*copy;
	int		idx;

	copy = ft_strdup(data->input);
	if (!copy)
		exit (1);
	idx = 0;
	while (copy[idx])
	{
		while (is_whitespace(copy[idx]))
			idx++;
		if (copy[idx])
			idx += add_lex_node(&copy[idx], &(data->lexer));
		/*if (id_token(&copy[idx]) == true)
		{
			printf("it's a token, %c\n", copy[idx]);
			idx += add_lex_node(&copy[idx], );
		}
			do thing where you save the token character in a node
		else if (id_word(&copy[idx]) == true)
		{
			printf(" it's a word\n");
			idx += add_lex_node(%copy[idx], )
			do thing where you save the word in a node
		}*/
	}
	//print_lex(data);
	free (copy);
	return (true);
}
