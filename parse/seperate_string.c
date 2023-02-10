/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:38:45 by codespace         #+#    #+#             */
/*   Updated: 2023/02/10 07:38:31 by codespace        ###   ########.fr       */
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

void	double_quote_task(char *return_val, t_list **root)
{
	int		index;
	int		index_before;

	index = 0;
	index_before = 0;
	while (return_val[index])
	{
		while (return_val[index] && return_val[index] != '$')
			index++;
		ft_lstadd_back(root, ft_lstnew(ft_substr(return_val, index_before, index - index_before), 0));
		index_before = index;
		if (return_val[index] && return_val[index] == '$' && (ft_isalpha(return_val[index + 1]) || return_val[index + 1] == '_'))
		{
			while (return_val[index] && (ft_isalnum(return_val[index + 1]) || return_val[index + 1] == '_'))
				index++;
			index++;
			ft_lstadd_back(root, ft_lstnew(ft_substr(return_val, index_before, index - index_before), 0));
			index_before = index;
		}
		else if (!ft_isalpha(return_val[index + 1]) || return_val[index + 1] != '_')
		{
			ft_lstadd_back(root, ft_lstnew(ft_substr(return_val, index, 2), 0));
			ft_lstlast(*root)->is_single_quote = 1;
			index += 2;
			index_before = index;
		}
	}	
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
			if (str[index] == '\"')
				double_quote_task(return_val, root);
			else
			{
				ft_lstadd_back(root, ft_lstnew(return_val, 0));
				ft_lstlast(*root)->is_single_quote = 1;
			}
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
	if (c == '|' || c == '>' || c == '<' || ft_iswhite(c) || c == '\'' || c == '\"' || c == '$')
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

char	*read_string_before_dollar(char *str, t_list **root)
{
	int		index;
	char	*return_val;
	
	index = 1;
	if (ft_isalpha(str[index]) || str[index] == '_')
		index++;
	else
	{
		printf("temp: syntax error near unexpected token \'$\'\n");
		exit(1);
	}
	while (str[index] && (ft_isalnum(str[index]) || str[index] == '_'))
		index++;
	return_val = ft_substr(str, 0, index);
	ft_lstadd_back(root, ft_lstnew(return_val, 0));
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
	else if (*str == '$')
		return_val = read_string_before_dollar(str, root);
	else
		return_val = str;
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

// int main()
// {
// 	char *return_val;
// 	return_val = getenv("dfasdfa");
// 	printf("return_val: %s\n", return_val);
// 	return (0);
// }

// this function make another t_list
// and return the new t_list
// it free the old t_list
// it merge the string in the t_list.
// ex) echo "l"s -> echo, ls
// ex2) echo "$HOME"s -> echo, /Users/jeonghyeonjeongs
// ex3) echo '$HOME's -> echo, $HOMEs

// void	merge_string_quote(t_list **temp, t_list **return_val)
// {
// 	char	*return_val_str;
// // write expressions on each code line
// 	return_val_str = (char *)malloc(sizeof(char) * 1);
// 	return_val_str[0] = '\0';
// 	while ((*temp)->next != NULL && (*temp)->next->is_meta == 0)
// 	{
// 		return_val_str = ft_strjoin(return_val_str, (*temp)->content);
// 		*temp = (*temp)->next;
// 	}
// 	ft_lstadd_back(return_val, ft_lstnew(return_val_str, 0));
// 	*temp = (*temp)->next;
// }

// void	merge_string_categorize(t_list **temp, t_list **return_val)
// {
// 	if ((*temp)->next != NULL && (*temp)->next->is_meta == 0)
// 		merge_string_quote(temp, return_val);
// 	else if ((*temp)->next != NULL && (*temp)->next->is_meta == 1)
// 		merge_string_meta(temp, return_val);
// 	else
// 	{
// 		ft_lstadd_back(return_val, ft_lstnew((*temp)->content, 0));
// 		*temp = (*temp)->next;
// 	}
// }

// t_list	*merge_string_set_cmd_option(t_list **root)
// {
// 	t_list	*temp;
// 	t_list	*return_val;

// 	temp = *root;
// 	while (temp)
// 		merge_string_categorize(&temp, &return_val);
// }

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
// make a test case main function
int main()
{
	t_list	*return_val;
	char	**return_val_char;
	int		index;

	index = 0;
	return_val = seperate_string("\"dsafj__$PATH---asdfjh$PATH2--xcv$PATH3$   $\"");
	set_pipe_n(&return_val);
	set_env(&return_val);
	t_list	*temp = return_val;

	while (temp)
	{
		printf("--------------------------\n");
		printf("is_meta: %d\n", temp->is_meta);
		printf("pipe_n: %d\n", temp->pipe_n);
		printf("content: $%s$\n", temp->content);
		printf("--------------------------\n");
		temp = temp->next;
	}
	return (0);
	
}
//  echo asdf | cat '$test'

// {   "'$test'"}