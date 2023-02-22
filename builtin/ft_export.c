/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:12:44 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/22 19:30:32 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// all meta character follows backslash in export
// 그냥 문자열로 들어왔을 때, 오류메세지 다르게 처리된다. -> 문자열임을 알아야 하나?
// 문자열 안에서 check_validate 다시 한 번 처리.
// 쉼표로 들어온 것에 대해서 파싱 처리 하기.
// 대치 필요

int	is_meta_builtin(char c)
{
	if (c == '!' || c == '@' || c == '$' || c == '^' || c == '%' || c == ':' \
	|| c == '*' || c == '[' || c == ']' || c == '/' || c == '{' || c == '}' \
	|| c == ',' || c == '.' || c == '?' || c == '+' || c == '~' || c == '-' \
	|| c == '=' || c == '\\' || c == '#' || c == '&' || c == '*' || c == '\'' \
	|| c == '\"' || c == '`' || c == '(' || c == ')' || c == '|' || c == ';' \
	|| c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_export_type(char *cmd)
{
	int	i;

	if (cmd[0] == '\0' || cmd[0] == '+' || cmd[0] == '=')
		return (0);
	i = 0;
	while (cmd[i] != '\0')
	{
		if (is_meta_builtin(cmd[i]))
		{
			if (cmd[i] == '=')
				return ('=');
			if (cmd[i] == '+' && cmd[i + 1] == '=')
				return ('+');
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_key(char *command)
{
	int		i;
	char	*key;

	i = 0;
	while (command[i] != '\0')
	{
		if (is_meta_builtin(command[i]))
			break ;
		i++;
	}
	key = (char *)malloc(sizeof(char *) * i + 1);
	if (key == NULL)
		return (NULL);
	i = 0;
	while (command[i] != '\0')
	{
		if (is_meta_builtin(command[i]))
			break;
		key[i] = command[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	get_value_len(char *command)
{
	int	i;
	int	val_count;

	i = 0;
	val_count = 0;
	while (command[i] != '\0')
	{
		if (val_count)
			val_count++;
		if (command[i] == '=' && !val_count)
			val_count = 1;
		i++;
	}
	return (val_count - 1);
}

char	*get_value(char *command)
{
	int		i;
	int		val_count;
	char	*value;

	val_count = get_value_len(command);
	if (val_count < 1)
		return (NULL);
	value = (char *)malloc(sizeof(char *) * val_count + 1);
	if (value == NULL)
		return (NULL);
	i = 0;
	val_count = 0;
	while (command[i] != '\0')
	{
		if (val_count)
			value[val_count++ - 1] = command[i];
		if (command[i++] == '=' && !val_count)
			val_count = 1;
	}
	value[val_count - 1] = '\0';
	return (value);
}

// value의 null값에 대해 생각해보기.
void	export_append(char *cmd, t_env *environ)
{
	char	*key;
	char	*value;
	char	*tmp;
	t_env	*cur;

	key = get_key(cmd);
	value = get_value(cmd);
	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key) + 1) == 0)
		{
			if (cur->val != NULL)
				tmp = ft_strjoin(cur->val, value);
			else
				tmp = ft_strdup(value);
			free(cur->val);
			cur->val = tmp;
			cur->export = 1;
			free(key);
			free(value);
			return ;
		}
		cur = cur->next;
	}
	add_environ(environ, key, value, 1);
}

void	export_replace(char *cmd, t_env *environ)
{
	char	*key;
	char	*value;
	t_env	*cur;

	key = get_key(cmd);
	value = get_value(cmd);
	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key) + 1) == 0)
		{
			free(cur->val);
			cur->val = value;
			cur->export = 1;
			free(key);
			return ;
		}
		cur = cur->next;
	}
	add_environ(environ, key, value, 1);
}

void	export_add(char *cmd, t_env *environ)
{
	t_env	*cur;
	int		found;
	char	*key;

	found = 0;
	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, cmd, ft_strlen(cur->key) + 1) == 0)
			found = 1;
		cur = cur->next;
	}
	key = ft_strdup(cmd); // only works for argv?
	if (!found)
		add_environ(environ, key, NULL, 0);
}

void	print_export_value(char *value)
{
	int	i;

	if (value == NULL)
		return ;
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\"')
		{
			ft_putchar_fd('\\', 1);
			ft_putchar_fd('\"', 1);
		}
		else
			ft_putchar_fd(value[i], 1);
		i++;
	}
}

void	show_export(t_env *environ)
{
	t_env	*cur;

	cur = environ;
	while (cur != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		if (cur->export)
		{
			ft_putstr_fd(cur->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			print_export_value(cur->val);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd(cur->key, 1);
			ft_putstr_fd("\n", 1);
		}
		cur = cur->next;
	}
}

int	ft_export(t_cmd *node, t_env *environ)
{
	int	i;
	int	type;

	i = 1;
	if (node->args[i] == NULL)
		show_export(environ);
	while (node->args[i] != NULL)
	{
		type = check_export_type(node->args[i]);
		if (!type)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(node->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		else if (type == '=')
			export_replace(node->args[i], environ);
		else if (type == '+')
			export_append(node->args[i], environ);
		else
			export_add(node->args[i], environ);
		i++;
	}
	return (EXIT_SUCCESS);
}
