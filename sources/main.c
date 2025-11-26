/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:23 by owen          #+#    #+#                 */
/*   Updated: 2025/11/26 11:25:26 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "parser.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	g_exit_code = 0;

static int	empty_line_exit(t_data *data)
{
	int	exit_code;

	exit_code = data->exit_code;
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_data(data);
	exit(exit_code);
}

static int	mini_loop(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		data->input = readline("minishell$ ");
		set_signals_noninteractive();
		if (g_exit_code == 130)
		{
			data->exit_code = g_exit_code;
			g_exit_code = 0;
		}
		if (!data->input)
			empty_line_exit(data);
		parse_input(data, data->input);
		if (data->commands)
		{
			execute_commands(data);
			reset_data(data, data->exit_code);
		}
	}
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
