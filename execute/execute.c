/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 01:31:40 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/22 03:39:33 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	execute_builtin(t_cmd *node, t_env *environ)
{
	int	ret;

	ret = 1;
	if (node->cmd == NULL)
		return (ret);
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
		ret = ft_echo(node);
	else if (ft_strncmp(node->cmd, "cd", 3) == 0)
		ret = ft_cd(node, environ);
	else if (ft_strncmp(node->cmd, "pwd", 4) == 0)
	{
		ft_putstr_fd("PROD: PWD EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "export", 7) == 0)
	{
		ft_putstr_fd("PROD: EXPORT EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "unset", 6) == 0)
	{
		ft_putstr_fd("PROD: UNSET EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "env", 4) == 0)
	{
		ft_putstr_fd("PROD: ENV EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "exit", 5) == 0)
	{
		ft_putstr_fd("PROD: EXIT EXECUTED\n", 1);
		exit(1);
	}
	return (ret);
}

// 따로 만들어야 하나?
int	execute_command_type(t_cmd *node, t_env *environ, int type)
{
	struct stat	sb;
	pid_t		pid;

	if (type)
		set_fd(node);
	if (execute_builtin(node, environ) == 1)
	{
		pid = fork();
		if (pid == -1)
			exit (1); // with error... but return or exit?
		else if (pid == 0)
		{
			if (stat(node->cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
				is_a_directory(node->cmd);
			if (execute_command(node, environ) == 1)
				command_not_found(node->cmd);
		}
		else
			if (waitpid(pid, NULL, 0) == -1)
				exit (1); // with error... but return or exit?
	}
	if (type)
		reset_fd(node);
	return (0);
}

void	pipeline_child(t_cmd *node, t_env *environ)
{
	int		pfd[2];
	pid_t	pid;

	ft_pipe(pfd);
	pid = fork();
	if (pid == -1)
		exit(1); // with error
	else if (pid == 0)
	{
		ft_close(pfd[READ_END]);
		ft_dup2(pfd[WRITE_END], STDOUT_FILENO);
		if (execute_command_type(node, environ, 0) == 1)
			command_not_found(node->cmd);
		else
			exit(0);
	}
	else
	{
		if (waitpid(pid, NULL, 0) == -1)
			exit(1); // with error
		ft_close(pfd[WRITE_END]);
		ft_dup2(pfd[READ_END], STDIN_FILENO);
	}
}

void	pipeline(t_cmd *node, t_env *environ)
{
	t_cmd	*cur;

	cur = node;
	while (cur->next != NULL)
	{
		if (cur->fd_in == -2)
			cur->fd_in = STDIN_FILENO;
		if (cur->fd_out == -2)
			cur->fd_out = STDOUT_FILENO;
		dup2(cur->fd_in, STDIN_FILENO);
		dup2(cur->fd_out, STDOUT_FILENO);
		pipeline_child(cur, environ);
		cur = cur->next;
	}
	if (execute_command_type(cur, environ, 0) == 1)
		command_not_found(cur->cmd);
	else
		exit(0);
}

// subshell 처리하기.
int	execute(t_cmd *line, t_env *environ)
{
	t_cmd	*node;
	pid_t	pid;

	if (line == NULL)
		return (1);
	node = line;
	if (node->next == NULL)
		return (execute_command_type(node, environ, 1));
	else
	{
		pid = fork();
		if (pid == -1)
			return (1); // with error
		else if (pid == 0)
			pipeline(node, environ);
		else
			if (waitpid(pid, NULL, 0) == -1)
				return (1); //with error
	}
	return (0);
}
