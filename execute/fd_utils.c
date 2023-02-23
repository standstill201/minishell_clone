/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:11:24 by gychoi            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/22 11:08:53 by codespace        ###   ########.fr       */
=======
/*   Updated: 2023/02/22 22:22:04 by gychoi           ###   ########.fr       */
>>>>>>> 2fa662aaee9f237c0ef2eefe04911853e47d1a49
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	set_fd(t_cmd *node)
{
	node->fd_old_in = dup(STDIN_FILENO);
	node->fd_old_out = dup(STDOUT_FILENO);
	if (node->fd_in == -2)
		node->fd_in = STDIN_FILENO;
	if (node->fd_out == -2)
		node->fd_out = STDOUT_FILENO;
	if (dup2(node->fd_in, STDIN_FILENO) == -1)
		execute_error("falied to dup2", PARENT);
	if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		execute_error("falied to dup2", PARENT);
}

void	reset_fd(t_cmd *node, int process_type)
{
	if (node->fd_old_in != -2)
		ft_dup2(node->fd_old_in, STDIN_FILENO, process_type);
	if (node->fd_old_out != -2)
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
