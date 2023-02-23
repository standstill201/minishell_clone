/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:11:24 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 10:05:33 by codespace        ###   ########.fr       */
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
	dup2(node->fd_in, STDIN_FILENO);
	dup2(node->fd_out, STDOUT_FILENO);
}

void	reset_fd(t_cmd *node, int process_type)
{
	dup2(node->fd_old_in, STDIN_FILENO);
	dup2(node->fd_old_out, STDOUT_FILENO);
}
