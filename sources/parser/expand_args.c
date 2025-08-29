/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/26 09:06:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/29 09:17:55 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_valid_var(char *str)
{
	(void)str;
	/*makes sure the characters, and order of characters, are valid*/
	return (false);
}

int	find_var_in_string(char *str, char *var)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		while (str[idx] != '$')
			idx++;
		if (str[idx] == '$')
		{
			if (!ft_strncmp(&str[idx + 1], var, ft_strlen(var)))
				return (idx);
			idx++;
		}
	}
	return (idx);
}

bool	reform_string(t_token *node, char *start, char *end, char *middle)
{
	char	*temp;

	temp = ft_strjoin(start, middle);
	if (!temp)
		return (false);
	free(node->string);
	node->string = ft_strjoin(temp, end);
	if (!node->string)
		return (free(temp), false);
	free(temp);
	return (true);
}

bool	rebuild_string(t_token *node, char *var, t_cd_ll_node *env_node)
{
	int		idx;
	char	*start;
	char	*end;

	//printf("string is %s\n", node->string);
	idx = find_var_in_string(node->string, var);
	start = ft_substr(node->string, 0, idx);
	end = ft_substr(node->string, (idx + ft_strlen(var) + 1), ft_strlen(&node->string[(idx + ft_strlen(var) + 1)]));
	reform_string(node, start, end, env_node->var_2);
	free(start);
	free(end);
	return (true);
}
	//printf("start has %s - var is %s - end has %s\n", start, var, end);
	// free(node->string);
	// temp = ft_strjoin(start, env_node->var_2);
	// free(start);
	// node->string = ft_strjoin(temp, end);
	// free(temp);

int	replace_var(t_cdllist *list, t_token *node, int idx)
{
	int				size;
	t_cd_ll_node	*var;
	char			*var_copy;

	size = (find_var_name(&node->string[idx + 1]) + 1);
	var_copy = (char *)malloc(sizeof(char) * (size + 1));
	if (!var_copy)
		/*implement malloc protection at a later date*/
		return (1);
	ft_strlcpy(var_copy, &node->string[idx + 1], size);
	//printf("%s\n", var_copy);
	var = cdll_get_node(list, 0, var_copy);
	if (!var)
		/*implement replace var_copy in original string with ' '*/
		printf("var not found\n");
		//exit(1);
	//else
		//printf("%s = %s\n", var->var_1, var->var_2);
		rebuild_string(node, var_copy, var);
	free(var_copy);
	return (size);
}

void	scan_expand(t_data *data, t_token *node)
{
	size_t	idx;

	idx = 0;
	//printf("%s\n", node->string);
	while (node->string[idx])
	{
		idx += find_dollar_sign(&node->string[idx]);
		if (idx == ft_strlen(node->string))
			return ;
		if (check_valid_var(&node->string[idx]) == true)
			replace_var(data->envp_copy, node, idx);
		else
			
		idx++;
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
