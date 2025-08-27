/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/26 09:06:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/27 14:40:07 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_valid_var(char *str)
{
	(void)str;
	/*makes sure the characters, and order of characters, are valid*/
	return (false);
}

bool	check_env_char(char c)
{
	if (ft_isalpha(c))
		return (true);
	else if (ft_isdigit(c))
		return (true);
	else if (c == '_')
		return (true);
	else if (c == '$')
		return (true);
	return (false);
}

size_t	find_var_name(char *str)
{
	size_t	size;

	size = 1;
	while (str[size])
	{
		if (check_env_char(str[size]) == false)
			return (size);
		size++;
	}
	return (size);
	
}

int	replace_var(t_cdllist *list, char *str)
{
	size_t			size;
	t_cd_ll_node	*var;
	char			*var_copy;


	if (str[0] != '$')
		return (0);
	size = find_var_name(str);
	var_copy = (char *)malloc(sizeof(char) * (size + 1));
	if (!var_copy)
		/*implement malloc protection at a later date*/
		return (1);
	ft_strlcpy(var_copy, (str + 1), size);
	//printf("var is %s\n", var_copy);
	var = cdll_get_node(list, 0, var_copy);
	if (!var)
		/*implement replace var_copy in original string with ' '*/
		printf("var not found\n");
	else
		printf("%s = %s\n", var->var_1, var->var_2);
	free(var_copy);
	return (size);
}

int	find_dollar_sign(char *str)
{
	size_t	idx;

	idx = 0;
	//printf("character to check is %c\n", str[idx]);
	while (str[idx] && str[idx] != '$')
		idx++;
	return (idx);
}

void	scan_expand(t_data *data, t_token *node)
{
	size_t	idx;

	idx = 0;
	//printf("%s\n", node->string);
	while (node->string[idx])
	{
		idx += find_dollar_sign(&node->string[idx]);
		idx += replace_var(data->envp_copy, &node->string[idx]);
		//printf("%zu strlen is %zu\n", idx, ft_strlen(node->string));
	}
	return ;
}

bool	expand_args(t_data *data)
{
	t_token	*copy;

	copy = data->lexer;
	while (copy)
	{
		if (copy->type == NOEXPAND)
			copy = copy->next;
		else
		{
			scan_expand(data, copy);
			copy = copy->next;
		}
	}
	return (true);
}
