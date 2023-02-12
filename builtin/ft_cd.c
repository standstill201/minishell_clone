/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:49:01 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/13 00:13:27 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// need to change ft_
int	cd_prev(void)
{
	// chdir(g_vars.prev_path);
	// g_vars.prev_path = getcwd(NULL, 0);
	// if (fail) error;
	// return (ret);
	return (0);
}

int	exec_cd(char *path)
{
	// g_vars.prev_path = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, path, strlen(path));
		write(2, ": No such file or directory\n", 29);
		return (-1);
	}
	printf("current directory : %s\n", getcwd(NULL, 0));
	return (0);
}

// prev_path needs to be managed by global variable
// path is changed only in the subshell, so check the path with printf
int	ft_cd(char **command)
{
	char	*cwd;
	int		ret;

	if (command[2] == NULL)
	{
		// g_vars.prev_path = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (-1);
		}
		printf("current directory : %s\n", getcwd(NULL, 0));
		return (0);
	}
	if (strncmp(command[2], "-", 2) == 0)
		ret = cd_prev();
	else
		ret = exec_cd(command[2]);
	return (ret);
}

int	main(int argc, char **argv)
{
	ft_cd(argv);
	return (0);
}
