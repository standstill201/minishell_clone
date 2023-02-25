/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:23:08 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/24 18:10:30 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

char	*find_path(char *command, char **envp)
{
	int		i;
	char	*path;
	char	*find;
	char	**paths;

	if (access(command, F_OK | X_OK) == 0)
		return (command);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	find = NULL;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], command);
		if (access(path, F_OK | X_OK) == 0)
			find = ft_strdup(path);
		free(path);
		free(paths[i++]);
	}
	free(paths);
	return (find);
}

static void	check_command_access(char *command)
{
	if (access(command, F_OK) == -1)
		no_such_file_or_directory(command);
	if (access(command, X_OK) == -1)
		permission_denied(command);
}

int	execute_command(t_cmd *node, char **envp)
{
	char	*command;
	char	*path;
	int		i;

	if (ft_strchr(node->cmd, '/'))
	{
		check_command_access(node->cmd);
		command = ft_strdup(node->cmd);
	}
	else
		command = ft_strjoin("/", node->cmd);
	path = find_path(command, envp);
	if (path == NULL || ft_strlen(node->cmd) == 0)
		return (1);
	if (execve(path, node->args, envp) == -1)
	{
		free(command);
		free(path);
		i = 0;
		while (envp[i] != NULL)
			free(envp[i++]);
		free(envp);
	}
	return (1);
}

int	retrieve_childs(t_cmd *line, pid_t pid, int *statloc, int process_type)
{
	t_cmd	*cur;
	pid_t	retrived;
	int		pid_statloc;

	cur = line;
	while (cur != NULL)
	{
		retrived = ft_wait(statloc, process_type);
		if (retrived == pid)
			pid_statloc = *statloc;
		cur = cur->next;
	}
	return (pid_statloc);
}

int	child_signal(int pid_status)
{
	if (WIFEXITED(pid_status))
		return (WEXITSTATUS(pid_status));
	else if (WTERMSIG(pid_status))
		return (128 + pid_status);
	else
		return (1);
}
