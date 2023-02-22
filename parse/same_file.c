/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   same_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:22:44 by codespace         #+#    #+#             */
/*   Updated: 2023/02/22 10:54:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_fd(t_list **pre_temp)
{
	t_list	*temp;

	temp = *pre_temp;
	while (temp)
	{
		if (temp->pipe_n != (*pre_temp)->pipe_n && temp->is_fd_input)
			temp->fd = (*pre_temp)->fd;
		temp = temp->next;
	}
	
}

void	*same_file(t_list **root)
{
	t_list	*temp;

	temp = *root;
	while (temp)
	{
		if (temp->is_fd_new || temp->is_fd_add)
			change_fd(&temp);
		temp = temp->next;
	}
}