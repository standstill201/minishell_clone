/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/21 11:48:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int is_ended;

void sigintHandler(int sig_num)
{
	is_ended = 1;
	write(STDOUT_FILENO, "\nminishell$ ", 12); // write a newline character to STDOUT
}

void handle_child_process(t_env *environ, int *status)
{
	char	*line;
	t_cmd	*line_root;

	line = readline("minishell$ ");
	// if (!line)
	// 	exit(0);
	if (line[0] != '\0')
		add_history(line);
	line_root = parse_data(line, status);
	if (!line_root)
	{
		free(line);
		return ;
	}
	// execute(line_root, environ);
	t_cmd *temp = line_root;
	while (temp)
	{
		printf("--------------------------\n");
		printf("cmd:%s$\n", temp->cmd);
		for (int i = 0; temp->args[i]; i++)
			printf("args%d:%s$\n", i, temp->args[i]);
		printf("fd_in: %d\n", temp->fd_in);
		printf("fd_out: %d\n", temp->fd_out);
		printf("pipe_n: %d\n", temp->pipe_n);
		printf("--------------------------\n");
		temp = temp->next;
	}
	free(line);
}

int main(int argc, char **argv, char **envp)
{
	t_env	*environ;
	int		status;

	status = 0;
	environ = set_environ(envp);
	signal(SIGINT, sigintHandler);
	while (1)
	{
		is_ended = 0;
		handle_child_process(environ, &status);
	}
	return 0;
}
