/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:50:45 by codespace         #+#    #+#             */
/*   Updated: 2023/02/12 10:50:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	up_digit(char *str, int index)
{
	str[index] = '!';
	if (index > 0)
	{
		if (str[index - 1] == '~')
			up_digit(str, index - 1);
		else
			str[index - 1]++;
	}
}

char	*name_creator(void)
{
	char	*str;
	int		index;

	str = ft_strdup("!!!!!");
	index = ft_strlen(str) - 1;
	while (access(str, F_OK) == 0)
	{
		if (str[index] == '~')
			up_digit(str, index);
		else
			str[index]++;
	}
	return (str);
}

int	read_heredoc_infile(char **av)
{
	int		fd;
	char	*line;
	char	*str;
	char	*lim;

	str = name_creator();
	fd = open(str, O_CREAT | O_RDWR, 0644);
	lim = (char *)ft_calloc(ft_strlen(av[2]) + 1, 1);
	ft_memcpy(lim, av[2], ft_strlen(av[2]));
	lim[ft_strlen(av[2])] = '\n';
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, lim, ft_strlen(line)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	unlink(str);
	free(str);
	free(lim);
	free(line);
	return (fd);
}
