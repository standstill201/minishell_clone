/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:22:00 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/20 20:38:04 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_meta(char c)
{
	// 메타 문자 확인하기
	if (c == '!' || c == '@' || c == '$' || c == '^' || c == '%' || c == ':' \
	|| c == '*' || c == '[' || c == ']' || c == '/' || c == '{' || c == '}' \
	|| c == ',' || c == '.' || c == '?' || c == '+' || c == '~' || c == '-' \
	|| c == '=' || c == '\\' || c == '#' || c == '&' || c == '*' || c == '\'' \
	|| c == '\"')
		return (1);
	return (0);
}

int	meta_exist(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (is_meta(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}


int	ft_unset(char **argv, t_env *environ)
{
	int	i;
	
	if (argv[1] != NULL)
	{
		i = 2;
		while (argv[i] != NULL)
		{
			if (meta_exist(argv[i]))
			{
				ft_putstr_fd("minishell: unset: `", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (EXIT_FAILURE);
			}
			delete_environ(environ, argv[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
//
//#include <stdio.h>
//#include <stdlib.h>
//void	leak_check(void)
//{
//	system("leaks --list -- a.out");
//}
//
//int	main(int argc, char **argv, char **envp)
//{
//	t_env	*environ;
//	t_env	*cur;
//	int	i;
//
//	environ = set_environ(envp);
//	ft_unset(argv, environ);
//	cur = environ;
//	while (cur != NULL)
//	{
//		printf("%s, %s, %d\n", cur->key, cur->val, cur->export);
//		cur = cur->next;
//	}
//	// need to clear envlist
//	env_lstclear(environ);
//	atexit(leak_check);
//	return (0);
//}
