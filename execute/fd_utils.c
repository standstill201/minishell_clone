/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:11:24 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/21 22:12:08 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	set_fd(t_cmd *node)
{
	if (node->fd_in != -2)
	{
		node->fd_old_in = dup(STDIN_FILENO);
		ft_dup2(node->fd_in, STDIN_FILENO);
	}
	if (node->fd_out != -2)
	{
		node->fd_old_out = dup(STDOUT_FILENO);
		ft_dup2(node->fd_out, STDOUT_FILENO);
	}
}

void	reset_fd(t_cmd *node)
{
	if (node->fd_old_in != -2)
	{
		ft_dup2(node->fd_old_in, STDIN_FILENO);
		node->fd_old_in = -2;
	}
	if (node->fd_old_out != -2)
	{
		ft_dup2(node->fd_old_out, STDOUT_FILENO);
		node->fd_old_out = -2;
	}
}
