/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:23 by owen          #+#    #+#                 */
/*   Updated: 2025/08/22 13:53:06 by owhearn       ########   odam.nl         */
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
		if (ft_strncmp(data->input, "exit", ft_strlen(data->input)) == 0)
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
	return (0);
}

void print_envp(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        printf("%s", envp[i]);
        i++;
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argv;
	ft_memset(&data, 0, sizeof(data));
	if (init_data(&data) == false)
		exit(1);
	print_envp(envp);
	//copy_env_data(&data, envp);
	if (argc > 1)
	{
		printf("This is not a thing anymore\n");
		exit(1);
		parse_input(&data, argv[1]);
	}
	else if (argc == 1)
		mini_loop(&data);
	//free(&data);
	exit (0);
}
