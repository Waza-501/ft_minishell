/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 11:35:30 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/05 12:00:51 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "structs.h"
# include <errno.h>

/*error_print.c*/
void		print_syntax_error(char *msg, char *token);
void		print_error(char *msg);
void		*malloc_error_print(char *msg);

/*error.c*/
void		free_data(t_data *data);
void		perror_exit(t_data *data);
void		*malloc_error(t_data *data, bool print);

#endif