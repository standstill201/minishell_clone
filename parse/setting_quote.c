/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:35:29 by codespace         #+#    #+#             */
/*   Updated: 2023/02/12 07:36:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	set_pipe_n(t_list **root)
{
	t_list	*temp;
	int		pipe_n;

	temp = *root;
	pipe_n = 0;
	while (temp)
	{
		temp->pipe_n = pipe_n;
		if (temp->is_meta && temp->content[0] == '|')
			pipe_n++;
		temp = temp->next;
	}
}

t_list	*string_merger(t_list *temp, t_list **return_val)
{
	char	*add_string;

	add_string = "";
	while (temp && temp->is_meta == 0)
	{
		add_string = ft_strjoin(add_string, temp->content);
		temp = temp->next;
	}
	ft_lstadd_back(return_val, ft_lstnew(add_string, 0));
	return (temp);
}

t_list	*merge_string(t_list **root)
{
	t_list	*temp;
	t_list	*return_val;

	return_val = ft_lstnew(ft_strdup("merge node start"), 0);
	temp = (*root)->next;
	while (temp)
	{
		if (temp->is_meta == 0)
			temp = string_merger(temp, &return_val);
		else
		{
			ft_lstadd_back(&return_val, ft_lstnew(ft_strdup(temp->content), 1));
			temp = temp->next;
		}
	}
	ft_lstclear(root, free);
	return (return_val);
}

void	set_env(t_list **root)
{
	t_list	*temp;
	char	*return_val;

	temp = *root;
	while (temp)
	{
		if (temp->is_meta == 0 && temp->content[0] == '$' && temp->is_single_quote == 0)
		{
			return_val = getenv(temp->content + 1);
			free(temp->content);
			if (return_val == NULL)
				temp->content = ft_strdup("");
			else
				temp->content = ft_strdup(return_val);
		}
		temp = temp->next;
	}
}