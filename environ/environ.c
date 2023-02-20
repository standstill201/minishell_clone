/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:05:27 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/20 14:12:02 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/environ.h"

char	*get_env(t_env *environ, char *key)
{
	t_env	*cur;

	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key) + 1) == 0)
			return (cur->val);
		cur = cur->next;
	}
	return (NULL);
}

char	**get_environ(t_env *environ)
{
	t_env	*cur;
	char	**envp;
	char	*tmp;
	int		i;

	envp = (char **)malloc(sizeof(char *) * env_lstlen(environ) + 1);
	if (envp == NULL)
		exit(1); // minishell error
	i = 0;
	cur = environ;
	while (cur != NULL)
	{
		if (cur->val == NULL)
			envp[i] = ft_strjoin(cur->key, "=");
		else
		{
			tmp = ft_strjoin("=", cur->val);
			envp[i] = ft_strjoin(cur->key, tmp);
			free(tmp);
		}
		i++;
		cur = cur->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	delete_environ(t_env *environ, char *key)
{
	t_env	*tmp;

	while (environ->next != NULL)
	{
		if (ft_strncmp(environ->next->key, key, \
			ft_strlen(environ->next->key) + 1) == 0)
		{
			tmp = environ->next;
			environ->next = tmp->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
		}
		environ = environ->next;
	}
}

void	add_environ(t_env *environ, char *key, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		exit(1);
		// minishell error
	new->key = key;
	new->val = val;
	new->next = NULL;
	env_lstadd_back(&environ, new);
}

t_env	*set_environ(char **envp)
{
	t_env	*environ;
	char	**envs;
	int		i;

	environ = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		envs = ft_split(envp[i], '=');
		if (envs == NULL)
			exit(1);
			//minishell_error("failed to create envp list");
		env_lstadd_back(&environ, env_lstnew(envs));
		free(envs);
		i++;
	}
	return (environ);
}

#include <stdio.h>
#include <stdlib.h>
void	leak_check(void)
{
	system("leaks --list -- a.out");
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*environ;
	t_env	*cur;
	char	*key;
	char	*value;
	char	**env_list;
	char	*find_env;
	int		i;

	environ = set_environ(envp);
	key = ft_strdup("test key");
	value = ft_strdup("test value");
	add_environ(environ, key, value);
	delete_environ(environ, "PATH");
	delete_environ(environ, "LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONG");
	env_list = get_environ(environ);
	i = 0;
	while (env_list[i] != NULL)
	{
		printf("%s\n", env_list[i]);
		i++;
	}
	find_env = get_env(environ, "USER");
	printf("find: %s\n", find_env);
	find_env = get_env(environ, "LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONG");
	printf("find: %s\n", find_env);
	env_lstclear(environ);
	i = 0;
	while (env_list[i] != NULL)
	{
		free(env_list[i]);
		i++;
	}
	free(env_list);
	atexit(leak_check);
	return (0);
}
