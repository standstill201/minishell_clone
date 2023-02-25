/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/24 22:23:42 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_is_ended;

void	free_parsed_data(t_cmd *line_root)
{
	t_cmd	*cur;
	t_cmd	*tmp;
	int		i;

	cur = line_root;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->cmd);
		i = 0;
		while (tmp->args[i] != NULL)
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		free(tmp);
	}
}

static void	check_leaks(void)
{
	system("leaks --list -- minishell");
}

void	sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
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
	// 임시!
	if (sig_num == SIGQUIT)
	{
		write(1, "exit...", 7);
		atexit(check_leaks);
		exit(0);
	}
}

void	handle_child_process(t_env *environ, int *status)
{
	char	*line;
	t_cmd	*line_root;
	int		tmp_fd;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler); // 임시
//	signal(SIGQUIT, SIG_IGN); // 이걸로 변환해야 합니다!

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
		free_parsed_data(line_root);
		return ;
	}
	// t_cmd *temp = line_root;
	// char *line_temp;
	// int fd;
	// while (temp)
	// {
	// 	printf("\n--------------------------\n");
	// 	printf("cmd:%s$\n", temp->cmd);
	// 	for (int i = 0; temp->args[i]; i++)
	// 		printf("args%d:%s$\n", i, temp->args[i]);
	// 	printf("fd_in: %d\n", temp->fd_in);
	// 	printf("fd_out: %d\n", temp->fd_out);
	// 	printf("pipe_n: %d\n", temp->pipe_n);
	// 	printf("\n--------------------------\n");
	// 	temp = temp->next;
	// }

	*status = execute(line_root, environ);
	free(line);
	free_parsed_data(line_root);
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
	env_lstclear(environ);
	return (0);
}
