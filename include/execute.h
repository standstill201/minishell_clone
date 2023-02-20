/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:19:23 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/20 20:55:42 by gychoi           ###   ########.fr       */
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

int	execute(t_cmd *root, t_env *environ);

void	command_not_found(char *command);

#endif
