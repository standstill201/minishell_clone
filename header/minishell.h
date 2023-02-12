/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:12 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/12 07:42:32 by codespace        ###   ########.fr       */
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
t_list	*parse_data(char *str);
t_list	*seperate_string(char *str);
void	set_pipe_n(t_list **root);
void	set_env(t_list **root);
t_list	*merge_string(t_list **root);
// meta_parse_part
char	*parse_meta(char *str, t_list **root);
int		is_meta(char c);
void	double_quote_task(char *return_val, t_list **root);
char	*read_string_before_redirection(char *str, t_list **root);
char	*read_string_before_dollar(char *str, t_list **root);
// meta_parse_part end

// parse_part end

// error_handle_part
void	sj_error(int errno);
// error_handle_part end

#endif