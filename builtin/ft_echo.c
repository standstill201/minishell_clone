/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:55:27 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/13 13:29:09 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	check_option(char *option)
{
	int	i;

	// need to convert ft_
	if (strncmp(option, "-n", 2) == 0)
	{
		i = 2;
		while (option[i] != '\0')
		{
			if (option[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

// void, or int?
// echo returns only EXIT_SUCCESS
int	ft_echo(char **command)
{
	int	i;
	int	option;

	i = 2;
	option = 0;
	if (command[i] && check_option(command[i]))
	{
		option = 1;
		i++;
	}
	while (command[i])
	{
		// need to convert ft_
		write(1, command[i], strlen(command[i]));
		if (command[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!option)
		write(1, "\n", 2);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	ft_echo(argv);
	return (0);
}
