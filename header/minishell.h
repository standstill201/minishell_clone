/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyoo <seokjyoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:12 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/01/30 17:31:16 by seokjyoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "../LIBFT/libft.h"

#define LINE_SPILL 0

typedef struct s_node {
	int				is_root_end;
	char			*data;
	struct s_node	*next_class;
}	t_node;

// parse_part
t_node	*parse_data(char *line);
// parse_part end

// error_handle_part
void	sj_error(int errno);
// error_handle_part end

#endif