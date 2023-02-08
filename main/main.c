/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyoo <seokjyoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/01/28 16:16:13 by seokjyoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(void)
{
	char	*line;
	t_node	*line_root;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (line[0] != '\0')
			add_history(line);
		line_root = parse_data(line);
		// run_process(parsed_line);
		free(line);
	}
}
