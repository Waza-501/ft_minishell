/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/25 17:49:43 by owhearn       #+#    #+#                 */
/*   Updated: 2025/08/25 18:04:30 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd_ll.h"
#include <string.h>
#include <stdio.h>

void print_list(t_cdllist *list)
{
    if (!list || !list->head)
    {
        printf("(empty list)\n");
        return;
    }
    t_cd_ll_node *cur = list->head;
    int count = 0;
    do
    {
        printf("[%d] var_1=\"%s\" var_2=\"%s\" id=%d\n",
               count, cur->var_1, cur->var_2, cur->id);
        cur = cur->next;
        count++;
    } while (cur != list->head);
}

int main(void)
{
    t_cdllist *list = cdll_init_list();
    if (!list)
    {
        fprintf(0, "Failed to init list\n");
        return 1;
    }
    cdll_add_back(list, cdll_new_node(strdup("foo"), strdup("bar"), 1));
    cdll_add_back(list, cdll_new_node(strdup("hello"), strdup("world"), 2));
    cdll_add_back(list, cdll_new_node(strdup("lorem"), strdup("ipsum"), 3));
    printf("List after 3 inserts:\n");
    print_list(list);
	cdll_del_list(list);
    return 0;
}
