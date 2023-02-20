/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:49:01 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/20 21:35:31 by gychoi           ###   ########.fr       */
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
