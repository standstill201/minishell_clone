/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:43:32 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/24 16:26:06 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	ft_close(int fd, int process_type)
{
	int	ret;

	ret = 0;
	if (close(fd) == -1)
		ret = execute_error("failed to close", process_type);
	return (ret);
}

int	ft_dup2(int fd1, int fd2, int process_type)
{
	int	ret;

	ret = 0;
	if (dup2(fd1, fd2) == -1)
		ret = execute_error("falied to dup2", process_type);
	if (fd1 != -2)
		ret = ft_close(fd1, process_type);
	return (ret);
}

int	ft_pipe(int *fd)
{
	int	ret;

	ret = 0;
	if (pipe(fd) == -1)
		ret = execute_error("failed to pipe", CHILD);
	return (ret);
}

int	ft_waitpid(pid_t pid, int *statloc, int options, int process_type)
{
	int	ret;

	ret = 0;
	if (waitpid(pid, statloc, options) == -1)
		ret = execute_error("failed to waitpid", process_type);
	return (ret);
}

pid_t	ft_wait(int *statloc, int process_type)
{
	pid_t	ret;

	ret = wait(statloc);
	if (ret == -1)
		execute_error("failed to wait", process_type);
	return (ret);
}
