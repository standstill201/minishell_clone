/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:05:54 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/24 18:35:38 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_error(char *message, int process_type)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	if (process_type == CHILD)
		exit(1);
	return (1);
}

void	no_such_file_or_directory(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

void	command_not_found(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	is_a_directory(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": is a directory\n", 2);
	exit(126);
}

void	permission_denied(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(126);
}
