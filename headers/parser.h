/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:18:22 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 13:33:23 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

/*parsing_utils, should probably be turned into is*/
int		is_whitespace(char c);
bool	is_space(const char *str);

/*parsing.c*/
int		parse_input(t_data *data, char *str);

#endif