/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/22 12:23:36 by codespace        ###   ########.fr       */
=======
/*   Updated: 2023/02/22 22:06:22 by gychoi           ###   ########.fr       */
>>>>>>> 2fa662aaee9f237c0ef2eefe04911853e47d1a49
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int is_ended;

void sigintHandler(int sig_num)
{
	if (is_ended == -1)
	{
		write(1, "\n", 1);
		close(0);
	}
	else
		write(1, "\nminishell$ ", 12);
	is_ended = 1;
}

void handle_child_process(t_env *environ, int *status)
{
	char	*line;
	t_cmd	*line_root;
	int		tmp_fd;

	tmp_fd = dup(0);
	is_ended = -1;
	line = readline("minishell$ ");
	if (is_ended > 0)
	{
		dup2(tmp_fd, 0);
		close(tmp_fd);
		return ;
	}
	if (is_ended == -1)
		is_ended = 0;
	if (!line)
	{
		write(1, "\n", 1);
		exit(0);
	}
	if (line[0] != '\0')
		add_history(line);
	line_root = parse_data(line, status);
	if (!line_root)
	{
		free(line);
		return ;
	}
	*status = execute(line_root, environ);
	t_cmd *temp = line_root;
	char *line_temp;
	int fd;
	while (temp)
	{
		printf("\n--------------------------\n");
		printf("cmd:%s$\n", temp->cmd);
		for (int i = 0; temp->args[i]; i++)
			printf("args%d:%s$\n", i, temp->args[i]);
		printf("fd_in: %d\n", temp->fd_in);
		printf("fd_out: %d\n", temp->fd_out);
		printf("pipe_n: %d\n", temp->pipe_n);
		printf("\n--------------------------\n");
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
	return (0);
}
