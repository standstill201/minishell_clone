/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:38:45 by codespace         #+#    #+#             */
/*   Updated: 2023/02/08 13:53:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <string.h>

// 1. seperate string by white space and special metacharacter |. each seperated string is named 'token'
// 2. if each token seperated by white space, intermidiate token is saved as a white space
// 3. if token is wrapped by double quotation or single quotation, it is saved as a single token
// 4. token is saved in a linked list
// example: echo hello world -> "echo", " ", "hello world"
// exmaple2: cat infile'|' | grep hello -> "cat", " ", "infile'|'", " ", "|", " ", "grep", " ", "hello"

// make a function seperate string by white space and special metacharacter |. each seperated string is named 'token'

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node -> content = content;
	new_node -> next = NULL;
	new_node -> is_meta = 0;
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_addr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_addr = ft_lstlast(*lst);
	last_addr -> next = new;
}

char	*read_string_before_quote(char *str, t_list **root)
{
	int		index;
	char	*return_val;
	char	trg;

	index = 0;
	trg = *str;
	str++;
	while (str[index])
	{
		if (str[index] == trg)
		{
			return_val = ft_substr(str, 0, index);
			ft_lstadd_back(root, ft_lstnew(return_val));
			return(str + index);
		}
		index++;
	}
	if (str[index] == '\0')
	{
		printf("temp: syntax error: unexpected end of file\n");
		exit(1);
	}
}

int	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' || ft_iswhite(c) || c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

char	*read_string_before_white_quote(char *str, t_list **root)
{
	int		index;
	char	*return_val;
	
	index = 0;
	while (str[index] && !is_meta(str[index]))
		index++;
	return_val = ft_substr(str, 0, index);
	ft_lstadd_back(root, ft_lstnew(return_val));
	return (str + index);
}

char	*read_string_before_redirection(char *str, t_list **root)
{
	char	*return_val;

	if (*(str + 1) && *(str + 1) == *(str))
	{
		return_val = (char *)malloc(sizeof(char) * 3);
		return_val[0] = *str;
		return_val[1] = *str;
		return_val[2] = 0;
		ft_lstadd_back(root, ft_lstnew(return_val));
		return (str + 2);
	}
	return_val = (char *)malloc(sizeof(char) * 2);
	return_val[0] = *str;
	return_val[1] = '\0';
	ft_lstadd_back(root, ft_lstnew(return_val));
	return (str + 1);
}

char	*read_string_before_pipe(char *str, t_list **root)
{
	int		index;
	char	*return_val;

	index = 0;
	str++;
	while (str[index])
	{
		if (str[index] == '|')
		{
			return_val = ft_substr(str, 0, index);
			ft_lstadd_back(root, ft_lstnew(return_val));
			return(str + index);
		}
		index++;
	}
	if (str[index] == '\0')
	{
		return_val = ft_substr(str, 0, index);
		ft_lstadd_back(root, ft_lstnew(return_val));
		return(str + index);
	}
}

char	*parse_meta(char *str, t_list **root)
{
	char	*return_val;
	
	printf("str : %s\n", str);
	if (*str == '\'' || *str == '\"')
		return_val = read_string_before_quote(str, root);
	else if (*str == '|')
		return_val = read_string_before_pipe(str, root);
	else if (*str == '>' || *str == '<')
		return_val = read_string_before_redirection(str, root);
	return (return_val);
}

t_list	*seperate_string(char *str)
{
	char	**return_val;
	t_list	*root;
	t_list	*temp;

	root = ft_lstnew("asdfasdf");
	temp = root;
	while (*str && ft_iswhite(*str))
		str++;
	while (*str)
	{
		if (is_meta(*str))
			str = parse_meta(str, &root);
		str = read_string_before_white_quote(str, &root);
		printf("return str: %s\n", str);
		// print node without changing node's address
		temp = root;
		while(temp)
		{
			printf("temp: %s\n", temp->content);
			temp = temp->next;
		}
		
	}
	return (root);
}

// make a test case main function
int main()
{
	t_list	*return_val;
	int		index;

	index = 0;
	return_val = seperate_string("echo\"|\" hello world");
	while (return_val)
	{
		// printf("temp: %s\n", return_val->content);
		return_val = return_val->next;
	}
	return (0);
}