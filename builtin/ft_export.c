/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:12:44 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/14 22:02:29 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "test_input.h"
#include <stdio.h>

// all meta character follows backslash in export
// 그냥 문자열로 들어왔을 때, 오류메세지 다르게 처리된다. -> 문자열임을 알아야 하나?
// 거대한 문자열은 따옴표가 들어왔을 때까지 처리?
// 대치 필요

int	is_meta(char c)
{
	// 메타 문자 확인하기
	if (c == '!' || c == '@' || c == '$' || c == '^' || c == '%' || c == ':' \
	|| c == '*' || c == '[' || c == ']' || c == '/' || c == '{' || c == '}' \
	|| c == ',' || c == '.' || c == '?' || c == '+' || c == '~' || c == '-' \
	|| c == '=' || ft_iswhite(c))
		return (1);
	return (0);
}

int	check_validate(char *env)
{
	int	i;

	if (env[0] == '\0' || env[0] == '+' || env[0] == '=')
		return (0);
	i = 0;
	while (env[i] != '\0')
	{
		if (is_meta(env[i]))
		{
			if (env[i] == '=')
				return (1);
			if (env[i] == '+' && env[i + 1] == '=')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_test_input *arr, char **argv)
{
	int	i;

	if (argv[1] != NULL)
	{
		i = 2;
		while (argv[i] != NULL)
		{
			if (!check_validate(argv[i]))
			{
				ft_putstr_fd("minishell: export: ", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd(": not a valid identifier\n", 2);
				return (EXIT_FAILURE);
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_test_input	*arr;
	int	i;

	arr = NULL;
	get_test_input(&arr);
	ft_export(arr, argv);
	return (0);
}
