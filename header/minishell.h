/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:12 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/10 04:25:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "../LIBFT/libft.h"

#define LINE_SPILL 0

// parse_part
t_list	*parse_data(char *line);
// parse_part end

// error_handle_part
void	sj_error(int errno);
// error_handle_part end

#endif