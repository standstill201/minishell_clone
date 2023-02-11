/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 04:24:16 by codespace         #+#    #+#             */
/*   Updated: 2023/02/10 07:01:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_list
{
	char			*content;
	int				pipe_n;
	int				is_meta;
	int				is_single_quote;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				pipe_n;
	struct s_cmd	*next;
}	t_cmd;

// aasdfxzcv$PATH---asdfxczvdsf
// aasdfxzcv$1PATH---asdfxczvdsf

#endif