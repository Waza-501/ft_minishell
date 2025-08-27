/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:23 by owen          #+#    #+#                 */
/*   Updated: 2025/08/27 18:11:38 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

bool	init_data(t_data *data)
{
	data->input = NULL;
	data->envp_copy = NULL;
	data->exit_code = 0;
	data->debug = true;
	data->error = false;
	data->lexer = NULL;
	return (true);
}

int	mini_loop(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		data->input = readline("minishell$ ");
		set_signals_noninteractive();
		if (ft_strlen(data->input) >= 4 && (ft_strncmp(data->input, "exit", 4) == 0))
			break ;
		// if (data->input[0] == 'f')
		// 	rl_clear_history();
		if (parse_input(data, data->input) == false)
		{
			if (data->error == true)
				exit (1);
		}
		free(data->input);
	}
	free(data->input);
	cdll_del_list(data->envp_copy);
	return (0);
}

void	print_envp(char **envp, t_cdllist *list)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	i = 0;
	while (i < list->size)
	{
		printf("%s\n", list->current->var_1);
		list->current = list->current->next;
		i++;
	}
	list->current = list->head;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	ft_memset(&data, 0, sizeof(data));
	if (init_data(&data) == false)
		exit(1);
	data.envp_copy = copy_envp(envp);
	if (!data.envp_copy)
		exit(1);
	//print_envp(envp, data.envp_copy);
	if (argc > 1)
	{
		printf("This is not a thing anymore\n");
		exit(1);
		//parse_input(&data, argv[1]);
	}
	else if (argc == 1)
		mini_loop(&data);
	//free(&data);
	exit (0);
}
