/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:19:23 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/24 18:06:34 by gychoi           ###   ########.fr       */
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
void	no_such_file_or_directory(char *command);
void	command_not_found(char *command);
void	is_a_directory(char *command);
void	permission_denied(char *command);

char	*find_path(char *command, char **envp);
int		execute_command(t_cmd *node, char **envp);
int		retrieve_childs(t_cmd *line, pid_t pid, int *statloc, int process_type);
int		child_signal(int pid_status);
int		execute(t_cmd *commandline, t_env *environ);

void	set_simple_command_fd(t_cmd *node, int process_type);
void	reset_simple_command_fd(t_cmd *node, int process_type);
void	set_command_fd(t_cmd *node);

int		ft_close(int fd, int process_type);
int		ft_dup2(int fd1, int fd2, int process_type);
int		ft_pipe(int *fd);
pid_t	ft_wait(int *statloc, int process_type);

#endif
