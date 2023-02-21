/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/21 06:38:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

// fix argc, argv
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*line;
// 	t_cmd	*line_root;
// 	t_env	*environ;
// 	pid_t	pid;

// 	environ = set_environ(envp);
// 	while (1)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			ft_putstr_fd("fork error\n", 2);
// 			exit(1);
// 		}
// 		else if (pid == 0)
// 		{
// 			line = readline("minishell$ ");
// 			if (!line)
// 				break;
// 			if (line[0] != '\0')
// 				add_history(line);
// 			line_root = parse_data(line);
// 			execute(line_root, environ);
// 			t_cmd	*temp = line_root;
// 			while (temp)
// 			{
// 				printf("--------------------------\n");
// 				printf("cmd:%s$\n", temp->cmd);
// 				for (int i = 0; temp->args[i]; i++)
// 					printf("args%d:%s$\n", i, temp->args[i]);
// 				printf("fd_in: %d\n", temp->fd_in);
// 				printf("fd_out: %d\n", temp->fd_out);
// 				printf("pipe_n: %d\n", temp->pipe_n);
// 				printf("--------------------------\n");
// 				temp = temp->next;
// 			}
// 			free(line);
// 			exit(0);
// 		}
// 		else
// 			wait(NULL);
// 	}
// }
void handle_child_process(t_env *environ, int status)
{
	char	*line;
	t_cmd	*line_root;

	line = readline("minishell$ ");
	// if (!line)
	// 	exit(0);
	if (line[0] != '\0')
		add_history(line);
	line_root = parse_data(line, &status);
	if (!line_root)
	{
		free(line);
		return ;
	}
	execute(line_root, environ);
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
	while (1)
	{
		handle_child_process(environ, status);
	}
	return 0;
}
