/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:07:03 by codespace         #+#    #+#             */
/*   Updated: 2023/02/21 11:58:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	char	*return_val;

	str = ft_strdup("!!!!!");
	return_val = ft_strjoin("/tmp/", str);
	index = ft_strlen(return_val) - 1;
	free(str);
	while (access(return_val, F_OK) == 0)
	{
		if (return_val[index] == '~')
			up_digit(return_val, index);
		else
			return_val[index]++;
		if (return_val[index] == '/')
			return_val[index] = 'f';
	}
	return (return_val);
}

void	free_everything(char *line, char *str, int fd, t_list *temp)
{
	unlink(str);
	free(line);
	free(str);
	close(fd);
	ft_lstclear(&temp, free);
}


int	read_heredoc_infile(char *limiter, t_list *temp, int *status)
{
	int		fd;
	char	*line;
	char	*str;

	str = name_creator();
	fd = open(str, O_CREAT | O_RDWR, 0644);
	line = get_next_line(STDIN_FILENO, 1);
	while (line && ft_strncmp(line, limiter, ft_strlen(line)))
	{
		if (is_ended)
		{
			free_everything(line, str, fd, temp);
			*status = 130;
			printf("!!!!!!!!!!!!!!!!!!!!\n");
			return (-2);
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO, 1);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	unlink(str);
	free(str);
	free(line);
	return (fd);
}



// need to think about ctrl -c and ctrl -d
