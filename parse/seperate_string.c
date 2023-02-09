/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:38:45 by codespace         #+#    #+#             */
/*   Updated: 2023/02/09 05:11:28 by codespace        ###   ########.fr       */
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
			ft_lstadd_back(root, ft_lstnew(return_val, 0));
			return(str + index + 1);
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
	ft_lstadd_back(root, ft_lstnew(return_val, 0));
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
		ft_lstadd_back(root, ft_lstnew(return_val, 1));
		return (str + 2);
	}
	return_val = (char *)malloc(sizeof(char) * 2);
	return_val[0] = *str;
	return_val[1] = '\0';
	ft_lstadd_back(root, ft_lstnew(return_val, 1));
	return (str + 1);
}

char	*read_string_before_pipe(char *str, t_list **root)
{
	int		index;
	char	*return_val;

	index = 0;
	str++;
	if (*str == '|')
	{
		printf("temp: syntax error near unexpected token \'|\'\n");
		exit(1);
	}
	return_val = (char *)malloc(sizeof(char) * 2);
	return_val[0] = '|';
	return_val[1] = '\0';
	ft_lstadd_back(root, ft_lstnew(return_val, 1));
	return (str);
}

char	*read_string_while_white(char *str, t_list **root)
{
	int		index;
	char	*return_val;
	
	index = 0;
	while (str[index] && ft_iswhite(str[index]))
		index++;
	return_val = ft_substr(str, 0, index);
	ft_lstadd_back(root, ft_lstnew(return_val, 1));
	return (str + index);
}

char	*parse_meta(char *str, t_list **root)
{
	char	*return_val;
	
	if (*str == '\'' || *str == '\"')
		return_val = read_string_before_quote(str, root);
	else if (*str == '|')
		return_val = read_string_before_pipe(str, root);
	else if (*str == '>' || *str == '<')
		return_val = read_string_before_redirection(str, root);
	else if (ft_iswhite(*str))
		return_val = read_string_while_white(str, root);
	return (return_val);
}

t_list	*seperate_string(char *str)
{
	char	**return_val;
	t_list	*root;

	root = ft_lstnew("head node start", 0);
	while (*str && ft_iswhite(*str))
		str++;
	while (*str)
	{
		if (is_meta(*str))
			str = parse_meta(str, &root);
		else
			str = read_string_before_white_quote(str, &root);
	}
	return (root);
}

// make a test case main function
int main()
{
	t_list	*return_val;
	int		index;

	index = 0;
	return_val = seperate_string("echo\"\"\'|\'\"\" >> hello world");
	while (return_val)
	{
		printf("--------------------------\n");
		printf("is_meta: %d\n", return_val->is_meta);
		printf("content: $%s$\n", return_val->content);
		printf("--------------------------\n");
		return_val = return_val->next;
	}
	return (0);
}