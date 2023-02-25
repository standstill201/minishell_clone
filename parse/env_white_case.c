/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_white_case.c.                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:19:23 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/24 18:06:34 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_string_before_white_quote_e(char *str, t_list **root)
{
	int		index;
	char	*return_val;

	index = 0;
	while (str[index] && !ft_iswhite(str[index]))
		index++;
	return_val = ft_substr(str, 0, index);
	ft_lstadd_back(root, ft_lstnew(return_val, 0));
	return (str + index);
}

t_list	*seperate_string_e(char *str, int pipe_n)
{
	t_list	*root;

	root = NULL;
	while (*str && ft_iswhite(*str))
		str++;
	while (*str)
	{
		if (ft_iswhite(*str))
		{
			ft_lstadd_back(&root, ft_lstnew(ft_strdup(" "), 1));
			ft_lstlast(root)->pipe_n = pipe_n;
			str++;
		}
		else
		{
			str = read_string_before_white_quote_e(str, &root);
			ft_lstlast(root)->pipe_n = pipe_n;
		}
		ft_lstlast(root)->is_single_quote = 1;
	}
	return (root);
}

void	env_white_case(t_list *temp)
{
	t_list	*result;
	t_list	*temp_next;

	result = seperate_string_e(temp->content, temp->pipe_n);
	temp_next = temp->next;
	free(temp->content);
	temp->content = ft_strdup(" ");
	temp->is_meta = 1;
	temp->next = result;
	ft_lstlast(result)->next = temp_next;
}

void	env_input(t_env *environ, t_list *temp, t_list **root)
{
	char	*return_val;

	return_val = get_env(environ, temp->content + 1);
	free(temp->content);
	if (return_val == NULL)
	{
		ft_strdup("");
		del_empty_envirnment(root, temp);
	}
	else
	{
		temp->content = ft_strdup(return_val);
		temp->is_env = 1;
		env_white_case(temp);
	}
}
