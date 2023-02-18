/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 05:55:43 by codespace         #+#    #+#             */
/*   Updated: 2023/02/17 12:24:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*parse_data(char *str)
{
	t_list	*parse_seperate;
	t_cmd	*return_val;
	int		index;

	index = 0;
	parse_seperate = seperate_string(str);
	set_here(&parse_seperate);
	set_pipe_n(&parse_seperate);
	set_env(&parse_seperate);
	if (ft_lstlast(parse_seperate)->content[0] == '|' && ft_lstlast(parse_seperate)->is_meta == 1)
	{
		ft_putstr_fd("minishell: not ended token `|'", 2);
		exit(1);//에러함수 만들기
	}
	parse_seperate = merge_string(&parse_seperate);
	del_redi_read_here(&parse_seperate);
	return_val = final_parse(&parse_seperate);
	return (return_val);
}
//echo adf | cat -e | asdf

// 1.input command -- ended--
// 2. <<
// 3. seperate command and redirection part
