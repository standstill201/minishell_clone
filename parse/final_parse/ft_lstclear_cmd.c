/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 02:30:16 by codespace         #+#    #+#             */
/*   Updated: 2023/02/17 10:56:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_double_pointer(char **args)
{
	int	index;

	index = 0;
	while (args[index])
	{
		free(args[index]);
		index++;
	}
	free(args);
}

void	ft_lstclear_cmd(t_cmd **lst)
{
	t_cmd	*temp;
	
	if (lst == NULL)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->cmd);
		free_double_pointer((*lst)->args);
		free(*lst);
		(*lst) = temp;
	}
	// 아직 안끝났음. 근데, 이거만 하면 릭은 안날거 같네요. 시간이 없어서 먼저 갑니다
}