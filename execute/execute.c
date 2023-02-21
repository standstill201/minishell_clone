/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:08:42 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/21 17:11:38 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

// return value에 대한 고민
int	execute_builtin(t_cmd *node, t_env *environ)
{
	int	ret;

	ret = 1;
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

int	execute_by_type(t_cmd *node, t_env *environ)
{
	struct stat	sb;
	pid_t		pid;
	int			status;

	status = execute_builtin(node, environ);
	if (status == 1)
	{
		pid = fork();
		if (pid == -1)
			minishell_error("failed to fork");
		else if (pid == 0)
		{
			if (stat(node->cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
				is_a_directory(node->cmd);
			status = execute_command(node, environ);
			if (status == 1)
				command_not_found(node->cmd);
		}
		else
			if (waitpid(pid, NULL, 0) == -1)
				minishell_error("failed to waitpid");
	}
	return (status);
}

// need to add FUNCTION_GUARD
// 에러 시 연결리스트 해제 필요? 혹은.. 가장 마지막에?
// 현재 25줄...
void	enter_pipeline(t_cmd *node, t_env *environ)
{
	int		pfd[2];
	pid_t	pid;

	ft_pipe(pfd);
	pid = fork();
	if (pid == -1)
		minishell_error("failed to fork");
	else if (pid == 0)
	{
		ft_close(pfd[READ_END]);
		if (node->fd_out == -2)
			node->fd_out = STDOUT_FILENO;
		ft_dup2(pfd[WRITE_END], node->fd_out);
		exit(execute_by_type(node, environ));
	}
	else
	{
		if (waitpid(pid, NULL, 0) == -1)
			minishell_error("failed to waitpid");
		ft_close(pfd[WRITE_END]);
		if (node->fd_in == -2)
			node->fd_in = STDIN_FILENO;
		ft_dup2(pfd[READ_END], node->fd_in);
	}
}

// execute 안에 파이프라인에서는 fork로 돌아가게...
int	execute(t_cmd *commandline, t_env *environ)
{
	t_cmd	*node;
	int		status;

	node = commandline;
	while (node->next != NULL)
	{
		enter_pipeline(node, environ);
		node = node->next;
	}
	return (execute_by_type(node, environ));
}
