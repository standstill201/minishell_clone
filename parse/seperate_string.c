/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:38:45 by codespace         #+#    #+#             */
/*   Updated: 2023/02/13 09:58:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


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


t_list	*seperate_string(char *str)
{
	t_list	*root;

	root = ft_lstnew(ft_strdup("root node start"), 0);
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

