/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/26 09:06:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/27 18:22:34 by owhearn       ########   odam.nl         */
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
	int	i;

	idx = 0;
	while (str[idx])
	{
		i = 0;
		while (str[idx] != '$')
			idx++;
		if (str[idx] == '$')
			if (!ft_strncmp(&str[idx + 1], var, ft_strlen(var)))
				return (idx);
	}
	return (idx);
}

bool	rebuild_string(char *str, char *var, t_cd_ll_node *node)
{
	int		idx;
	char	*start;
	char	*temp;
	char	*end;

	printf("string is %s\n", str);
	idx = find_var_in_string(str, var);
	start = ft_substr(str, 0, idx);
	end = ft_substr(str, (idx + ft_strlen(var) + 1), ft_strlen(&str[(idx + ft_strlen(var) + 1)]));
	printf("start has %s - var is %s - end has %s\n", start, var, end);
	free(str);
	temp = ft_strjoin(start, node->var_2);
	free(start);
	str = ft_strjoin(temp, end);
	free(temp);
	free(end);
	return (true);
}

int	replace_var(t_cdllist *list, char *str, int idx)
{
	int				size;
	t_cd_ll_node	*var;
	char			*var_copy;


	// if (str[0] != '$')
	// 	return (0);
	size = (find_var_name(&str[idx + 1]) + 1);
	var_copy = (char *)malloc(sizeof(char) * (size + 1));
	if (!var_copy)
		/*implement malloc protection at a later date*/
		return (1);
	ft_strlcpy(var_copy, &str[idx + 1], size);
	printf("%s\n", var_copy);
	var = cdll_get_node(list, 0, var_copy);
	if (!var)
		/*implement replace var_copy in original string with ' '*/
		//printf("var not found\n");
		exit(1);
	else
		//printf("%s = %s\n", var->var_1, var->var_2);
		rebuild_string(str, var_copy, var);
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
		replace_var(data->envp_copy, node->string, idx);
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
