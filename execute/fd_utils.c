/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:11:24 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/24 02:21:04 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	set_simple_command_fd(t_cmd *node, int process_type)
{
	if (node->fd_in == -2)
		node->fd_in = dup(STDIN_FILENO);
	if (node->fd_out == -2)
		node->fd_out = dup(STDOUT_FILENO);
	node->fd_old_in = dup(STDIN_FILENO);
	node->fd_old_out = dup(STDOUT_FILENO);
	ft_dup2(node->fd_in, STDIN_FILENO, process_type);
	ft_dup2(node->fd_out, STDOUT_FILENO, process_type);
}

void	reset_simple_command_fd(t_cmd *node, int process_type)
{
	ft_dup2(node->fd_old_in, STDIN_FILENO, process_type);
	ft_dup2(node->fd_old_out, STDOUT_FILENO, process_type);
}

void	set_command_fd(t_cmd *node)
{
	if (node->fd_in != -2)
		ft_dup2(node->fd_in, STDIN_FILENO, CHILD);
	if (node->fd_out != -2)
		ft_dup2(node->fd_out, STDOUT_FILENO, CHILD);
}
