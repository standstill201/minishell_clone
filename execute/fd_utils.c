/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:11:24 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 17:22:26 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	set_fd(t_cmd *node, int process_type)
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

void	reset_fd(t_cmd *node, int process_type)
{
	ft_dup2(node->fd_old_in, STDIN_FILENO, process_type);
	ft_dup2(node->fd_old_out, STDOUT_FILENO, process_type);
}

void	set_pipeline_fd(t_cmd *node)
{
	if (node->fd_in == -2)
		node->fd_in = STDIN_FILENO;
	if (node->fd_out == -2)
		node->fd_out = STDOUT_FILENO;
	if (dup2(node->fd_in, STDIN_FILENO) == -1)
		execute_error("falied to dup2", CHILD);
	if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		execute_error("falied to dup2", CHILD);
}
