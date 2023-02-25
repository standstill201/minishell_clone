/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:35:29 by codespace         #+#    #+#             */
/*   Updated: 2023/02/24 21:51:39 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*string_merger(t_list *temp, t_list **return_val)
{
	char	*add_string;
	char	*temp_string;
	int		pipe_n;
	int		here_word_trg;

	add_string = malloc(sizeof(char));
	add_string[0] = '\0';
	here_word_trg = 0;
	pipe_n = temp->pipe_n;
	while (temp && temp->is_meta == 0)
	{
		if (temp->is_here_word)
			here_word_trg = 1;
		temp_string = ft_strdup(add_string);
		free(add_string);
		add_string = ft_strjoin(temp_string, temp->content);
		free(temp_string);
		temp = temp->next;
	}
	ft_lstadd_back(return_val, ft_lstnew(add_string, 0));
	ft_lstlast(*return_val)->pipe_n = pipe_n;
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
	return (return_val);
}

void	del_empty_envirnment(t_list **root, t_list *temp)
{
	t_list	*pre_temp;

	pre_temp = *root;
	while (pre_temp)
	{
		if (pre_temp->next == temp)
		{
			pre_temp->next = temp->next;
			ft_lstdelone(temp, free);
			break ;
		}
		pre_temp = pre_temp->next;
	}
}

void	question_mark_extention(t_list *temp, int *status)
{
	free(temp->content);
	temp->content = ft_itoa(*status);
}

t_list	*seperate_string_e(char *str, int pipe_n, char c)
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
			str = read_string_before_white_quote(str, &root);
			ft_lstlast(root)->pipe_n = pipe_n;
		}
		if (c == '\'')
		{
			ft_lstlast(root)->is_single_quote = 1;
		}
	}
	return (root);
}

void	env_white_case(t_list *temp, t_list **root)
{
	t_list	*result;
	t_list	*temp_next;
	int		temp_n;

	result = seperate_string_e(temp->content, temp->pipe_n, temp->content[0]);
	temp_next = temp->next;
	free(temp->content);
	temp->content = ft_strdup(" ");
	temp->is_meta = 1;
	temp->next = result;
	ft_lstlast(result)->next = temp_next;
	
}

void	set_env(t_list **root, int *status, t_env *environ)
{
	t_list	*temp;
	char	*return_val;

	temp = *root;
	while (temp)
	{
		if (temp->is_meta == 0 && temp->content[0] == '?'
			&& temp->is_single_quote == 0 && temp->is_question_dollor && !temp->is_env)
			question_mark_extention(temp, status);
		else if (temp->is_meta == 0
			&& temp->content[0] == '$' && temp->is_single_quote == 0 && !temp->is_env)
		{
			return_val = get_env(environ, temp->content + 1);
			printf("str: %s\n", return_val);
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
				env_white_case(temp, root);
			}
		}
		temp = temp->next;
	}
}


// for_reverse->next = ft_lstnew(" ", 1);
// 		for_reverse = for_reverse->next;
// 		for_reverse->is_env = 1;
// 		for_reverse->next = ft_lstnew(str, 0);
// 		for_reverse->next->is_env = 1;
// 		for_reverse->next->next = temp_next;
