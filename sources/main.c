/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:23 by owen          #+#    #+#                 */
/*   Updated: 2025/11/10 14:59:26 by haile         ########   odam.nl         */
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
		// printf("last exit code: %i REMOVE AFTER TESTING\n", data->exit_code);
		if (!data->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
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


void	print_envp(char **envp, t_cdllist *list)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	i = 0;
	while (i < list->size)
	{
		printf("%s = %s\n", list->current->var_1, list->current->var_2);
		list->current = list->current->next;
		i++;
	}
	list->current = list->head;
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
