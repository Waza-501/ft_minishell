/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:23 by owen          #+#    #+#                 */
/*   Updated: 2025/11/04 13:31:45 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "parser.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	g_exit_code = 0;

/*wipe all data from data*/
int	reset_data(t_data *data, int code)
{
	ft_free(&data->input);
	if (data->lexer)
		clear_lexer(data);
	if (data->commands)
		clear_commands(data);
	data->exit_code = code;
	return (0);
}

t_data	*init_data(void)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->input = NULL;
	new->envp_copy = NULL;
	new->lexer = NULL;
	new->commands = NULL;
	new->exit_code = 0;
	return (new);
}

int	mini_loop(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		data->input = readline("minishell$ ");
		set_signals_noninteractive();
		printf("last exit code: %i\n", data->exit_code);
		if (!data->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		if (ft_strlen(data->input) >= 4
			&& (ft_strncmp(data->input, "exit", 4) == 0))
			break ;
		parse_input(data, data->input);
		if (data->commands)
		{
			printf("Commands ready for execution\n");
			execute_commands(data);
			reset_data(data, 0);
		}
	}
	free_structs(data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = init_data();
	if (!data)
		exit(1);
	data->envp_copy = copy_envp(envp);
	if (!data->envp_copy)
		exit(1);
	if (argc > 1)
	{
		printf("minishell$ This project only runs in interactive mode.\n");
		exit(0);
	}
	else if (argc == 1)
		mini_loop(data);
	return (0);
}
