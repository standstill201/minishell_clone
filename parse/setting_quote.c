/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:35:29 by codespace         #+#    #+#             */
/*   Updated: 2023/02/15 19:44:33 by codespace        ###   ########.fr       */
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
	char	*temp_string;
	int		pipe_n;
	int		here_word_trg_q;
	int		here_word_trg;

	add_string = "";
	here_word_trg_q = 0;
	here_word_trg = 0;
	pipe_n = temp->pipe_n;
	while (temp && temp->is_meta == 0)
	{
		if (temp->is_here_quote_word)
			here_word_trg_q = 1;
		if (temp->is_here_word)
			here_word_trg = 1;
		temp_string = ft_strdup(add_string);
		add_string = ft_strjoin(temp_string, temp->content);
		free(temp_string);
		temp = temp->next;
	}
	ft_lstadd_back(return_val, ft_lstnew(add_string, 0));
	ft_lstlast(*return_val)->pipe_n = pipe_n;
	if (here_word_trg_q)
		ft_lstlast(*return_val)->is_here_quote_word = 1;
	if (here_word_trg)
		ft_lstlast(*return_val)->is_here_word = 1;
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
		else if (temp->is_meta == 1 && temp->content[0] != '|')
		{
			ft_lstadd_back(&return_val, ft_lstnew(ft_strdup(temp->content), 1));
			ft_lstlast(return_val)->pipe_n = temp->pipe_n;
			temp = temp->next;
		}
		else
			temp = temp->next;
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