/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 07:28:27 by codespace         #+#    #+#             */
/*   Updated: 2023/02/17 10:56:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' || ft_iswhite(c) ||
	c == '\'' || c == '\"' || c == '$' || c == ';' || c == '\\')
		return (1);
	else
		return (0);
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
		unexpected_token_end();
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