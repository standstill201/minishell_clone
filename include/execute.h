/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:19:23 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/21 16:59:01 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include "environ.h"
# include "builtin.h"
# include <sys/wait.h>
# include <sys/stat.h>

# define READ_END	0
# define WRITE_END	1

void	command_not_found(char *command);
void	is_a_directory(char *command);

void	ft_close(int fd);
void	ft_dup2(int fd1, int fd2);
void	ft_pipe(int *fd);

char	*find_path(char *command, char **envp);
int		execute_command(t_cmd *node, t_env *environ);
int		execute(t_cmd *commandline, t_env *environ);


#endif
