/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:36:38 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/14 15:21:06 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "structs.h"

/*expand_core*/
int		expand_args(t_data *data);

/*expand_args*/
int		scan_expand(t_data *data, t_lexer *node);

/*expand_utils.c*/
bool	check_env_char(char c);
int		find_dollar_sign(char *str);
int		find_var_size(char *str);
int		find_var_in_string(char *str, char *var);
bool	reform_string(t_lexer *node, char *start, char *end, char *middle);

#endif