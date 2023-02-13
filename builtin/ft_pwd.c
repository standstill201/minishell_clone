/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:25:17 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/13 14:13:18 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// need to change ft_
int	ft_pwd(char **command)
{
	char	*path;

	if (command == NULL || command[1] == NULL)
		return (EXIT_FAILURE);
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (EXIT_FAILURE);
	write(1, path, strlen(path));
	write(1, "\n", 1);
	free(path);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	ft_pwd(argv);
	return (0);
}
