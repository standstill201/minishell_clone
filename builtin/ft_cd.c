/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:49:01 by gychoi            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/20 21:35:31 by gychoi           ###   ########.fr       */
=======
/*   Updated: 2023/02/20 08:14:28 by codespace        ###   ########.fr       */
>>>>>>> 98773ca3979b4d8fba231b791d099fb0664f038f
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	ft_cd(t_cmd *node, t_env *environ)
{
	char	*cwd;
	int		ret;

	if (node->args[1] == NULL)
	{
		if (chdir(get_env(environ, "HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	if (chdir(node->args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*ft_cd_master(t_cmd *node, t_env *environ)
{
	char	*cwd;
	int		ret;

	if (node->args[1] == NULL)
	{
		if (chdir(get_env(environ, "HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (getcwd(NULL, 0));
	}
	if (chdir(node->args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	return (getcwd(NULL, 0));
}
