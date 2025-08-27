/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_ll.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/25 15:01:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/27 14:56:43 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_LL_H
# define CD_LL_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_cd_node
{
	char				*var_1;
	char				*var_2;
	int					id;
	struct s_cd_node	*next;
	struct s_cd_node	*prev;
}						t_cd_ll_node;

typedef struct s_cdllist
{
	t_cd_ll_node	*head;
	t_cd_ll_node	*current;
	int				size;
}					t_cdllist;

/*cd_ll_addback.c*/
void			cdll_add_back(t_cdllist *list, t_cd_ll_node *node);

/*cd_ll_addfront.c*/
void			cdll_add_front(t_cdllist *list, t_cd_ll_node *node);

/*cd_ll_del_list.c*/
void			cdll_del_list(t_cdllist *list);
/*cd_ll_del_node.c*/
void			cdll_del_node(t_cdllist *list, bool clear, char *name);

/*cd_ll_get_node.c*/
t_cd_ll_node	*cdll_get_node(t_cdllist *list, bool clear, char *name);

/*cd_ll_init.c*/
t_cdllist		*cdll_init_list(void);

/*cd_ll_new_node.c*/
t_cd_ll_node	*cdll_new_node(char *str1, char *str2, int id);

/*cd_ll_utils.c*/
size_t			cdll_strlen(const char *s);
int				cdll_strncmp(const char *s1, const char *s2, size_t n);

#endif