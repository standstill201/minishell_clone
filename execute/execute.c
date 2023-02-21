/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:08:42 by gychoi            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/21 09:44:39 by codespace        ###   ########.fr       */
=======
/*   Updated: 2023/02/21 20:49:39 by gychoi           ###   ########.fr       */
>>>>>>> 0154b382d87952f3e7cfd61ff6bfa890f3bace0c
/*                                                                            */
/* ************************************************************************** */

/*
#include "../include/execute.h"

// return value에 대한 고민
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

int	execute_by_type(t_cmd *node, t_env *environ)
{
	struct stat	sb;
	pid_t		pid;

	set_fd(node);
	if (execute_builtin(node, environ) == 1)
	{
		pid = fork();
		if (pid == -1)
		{
			reset_fd(node);
			return (global_execute_error("failed to fork\n")); // exit?
		}
		else if (pid == 0)
		{
			if (stat(node->cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			{
				reset_fd(node);
				is_a_directory(node->cmd);
			}
			if (execute_command(node, environ) == 1)
			{
				reset_fd(node);
				command_not_found(node->cmd);
			}
		}
		else
			if (waitpid(pid, NULL, 0) == -1)
				return (global_execute_error("failed to waitpid\n")); // 오류에 대해 모두 초기화?
	}
	reset_fd(node);
	return (1);
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
		global_execute_error("failed to fork");
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
			global_execute_error("failed to waitpid");
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
	pid_t	pid;
	int		status;

	node = commandline;
	if (node->next != NULL)
	{
		pid = fork();
		if (pid == -1)
			return (global_execute_error("falied to fork"));
		else if (pid == 0)
		{
			while (node->next != NULL)
			{
				enter_pipeline(node, environ);
				node = node->next;
			}
		}
		else
			if (waitpid(pid, NULL, 0) == -1)
				return (global_execute_error("failed to fork"));
	}
	printf("fds: %d, %d, %d, %d\n", node->fd_in, node->fd_out, node->fd_old_in, node->fd_old_out);
	return (execute_by_type(node, environ));
}
*/
