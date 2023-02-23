/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:19:23 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/23 08:22:52 by codespace        ###   ########.fr       */
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
# define PARENT	2
# define CHILD	4

int		execute_error(char *message, int process_type);
void	execute_command_error(char *command);
void	command_not_found(char *command);
void	is_a_directory(char *command);

void	ft_close(int fd, int process_type);
void	ft_dup2(int fd1, int fd2, int process_type);
void	ft_pipe(int *fd);

char	*find_path(char *command, char **envp);
int		execute_command(t_cmd *node, char **envp);
int		execute(t_cmd *commandline, t_env *environ);

void	set_fd(t_cmd *node);
void	reset_fd(t_cmd *node, int process_type);
void	set_pipeline_fd(t_cmd *node);

void	reset_pipeline_fd(t_cmd *node);

#endif
