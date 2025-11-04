/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:18:22 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 18:07:34 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

/*parsing_utils, should probably be turned into is*/
bool	is_token(char *str);
bool	is_quotes(char c);
int		is_whitespace(char c);
bool	is_space(const char *str);

/*lexer_utils.c*/
char	*strcpy_delim(char *str, char delim1, char delim2, char delim3);

/*lexer.c*/
bool	setup_lexer(t_data *data);

/*parsing.c*/
int		parse_input(t_data *data, char *str);

/*handle_quotes.c*/
int		is_quoted(char *str);
int		remove_quotes(t_data *data, t_lexer *node);

/**/
bool	assign_type(t_data *data);

/*concatenate_strings*/
bool	concatenate_strings(t_data *data);

#endif