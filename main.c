/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/24 18:39:10 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_is_ended;

void	sigint_handler(int sig_num)
{
	if (g_is_ended == -1)
	{
		write(1, "\n", 1);
		close(0);
	}
	else
		write(1, "\nminishell$ ", 12);
	g_is_ended = 1;
}

void	handle_child_process(t_env *environ, int *status)
{
	char	*line;
	t_cmd	*line_root;
	int		tmp_fd;

	signal(SIGINT, sigint_handler);
	tmp_fd = dup(0);
	g_is_ended = -1;
	line = readline("minishell$ ");
	if (g_is_ended > 0)
	{
		dup2(tmp_fd, 0);
		close(tmp_fd);
		return ;
	}
	if (g_is_ended == -1)
		g_is_ended = 0;
	if (!line)
	{
		write(1, "\n", 1);
		exit(0);
	}
	if (line[0] != '\0')
		add_history(line);
	line_root = parse_data(line, status, environ);
	if (!line_root)
	{
		free(line);
		return ;
	}
	*status = execute(line_root, environ);
	free(line);
}


int	main(int argc, char **argv, char **envp)
{
	t_env	*environ;
	int		status;

	status = 0;
	environ = set_environ(envp);
	while (1)
	{
		g_is_ended = 0;
		handle_child_process(environ, &status);
	}
	return (0);
}
