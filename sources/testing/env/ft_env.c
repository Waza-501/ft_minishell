/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 11:52:30 by haile         #+#    #+#                 */
/*   Updated: 2025/09/05 11:53:41 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int ft_env(char **env)
{
    int i;

    i = 0;
    if (!env)
        return (1);
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}