/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/22 13:19:53 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 18:08:41 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	is_quoted(char *str)
{
	if (is_quotes(str[0]) == true && is_quotes(str[ft_strlen(str)] == true))
		return (1);
	return (0);
}

static size_t	strlen_without_quotes(char *str)
{
	int		i;
	char	c;
	size_t	idx;

	i = 0;
	idx = 0;
	while (str[i])
	{
		if (str[i] == S_Q || str[i] == D_Q)
		{
			c = str[i++];
			while (str[i] != c)
			{
				idx++;
				i++;
			}
			i++;
		}
		else
		{
			idx++;
			i++;
		}
	}
	return (idx);
}

/*will need to be renamed*/
static int	reform_str(char *str, char *new)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == S_Q || str[i] == D_Q)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				new[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (0);
}

int	remove_quotes(t_data *data, t_lexer *node)
{
	int		i;
	int		idx;
	char	*new;

	i = 0;
	idx = (int)strlen_without_quotes(node->string);
	new = (char *)malloc(sizeof(char) * idx + 1);
	if (!new)
		malloc_error(data, true);
	reform_str(node->string, new);
	ft_free(&node->string);
	node->string = new;
	return (0);
}
