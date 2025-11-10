/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:23 by owen          #+#    #+#                 */
/*   Updated: 2025/11/10 03:23:25 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include "parser.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	g_exit_code = 0;

static int	mini_loop(t_data *data)
{
	t_shell	*shell;
	shell = init_shell(data);
	if (!shell)
		return (1);
	while (1)
	{
		set_signals_interactive();
		data->input = readline("minishell$ ");
		set_signals_noninteractive();
		printf("last exit code: %i REMOVE AFTER TESTING\n", data->exit_code);
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
			execute_with_shell(shell, data);
			reset_data(data, 0);
		}
	}
	cleanup_shell(shell);
	free_data(data);
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
