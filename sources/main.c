/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:23 by owen          #+#    #+#                 */
/*   Updated: 2025/10/22 16:46:47 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

t_data	*init_data(void)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->input = NULL;
	new->envp_copy = NULL;
	new->exit_code = 0;
	new->lexer = NULL;
	new->commands = NULL;
	return (new);
}

// if (data->input[0] == 'f')
// 	rl_clear_history();
int	mini_loop(t_data *data)
{
	while (1)
	{
		set_signals_interactive();
		data->input = readline("minishell$ ");
		set_signals_noninteractive();
		if (!data->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(1);
		}
		if (ft_strlen(data->input) >= 4
			&& (ft_strncmp(data->input, "exit", 4) == 0))
			break ;
		if (parse_input(data, data->input) == false)
		{
			free_structs(data);
			exit (1);
		}
		/*execution would go here*/
		free(data->input);
		clear_commands(data);
	}
	free(data->input);
	cdll_del_list(data->envp_copy);
	return (0);
}

// void	print_envp(char **envp, t_cdllist *list)
// {
// 	int	i;
//
// 	i = 0;
// 	while (envp[i])
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < list->size)
// 	{
// 		printf("%s\n", list->current->var_1);
// 		list->current = list->current->next;
// 		i++;
// 	}
// 	list->current = list->head;
// }

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
		exit(1);
	}
	else if (argc == 1)
		mini_loop(data);
	free(data);
	return (0);
}
