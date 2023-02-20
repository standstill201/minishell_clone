/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:19:23 by gychoi            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/20 20:55:42 by gychoi           ###   ########.fr       */
=======
/*   Updated: 2023/02/20 11:43:34 by codespace        ###   ########.fr       */
>>>>>>> 98773ca3979b4d8fba231b791d099fb0664f038f
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

void	execute(t_cmd *root, t_env *environ);

void	command_not_found(char *command);

#endif
