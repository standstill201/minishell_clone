/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:23:08 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/21 21:50:43 by gychoi           ###   ########.fr       */
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

int	execute_command(t_cmd *node, t_env *environ)
{
	char	*command;
	char	*path;
	char	**envp;
	int		i;

	// check subshell
	if (ft_strchr(node->cmd, '/') && access(node->cmd, F_OK | X_OK) == -1)
		execute_error(node->cmd);
	command = ft_strjoin("/", node->cmd);
	envp = get_environ(environ);
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
	printf("hello\n");
	return (1);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		global_execute_error("failed to close\n");
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		global_execute_error("falied to dup2\n");
	if (fd1 != -2)
		ft_close(fd1);
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
		global_execute_error("failed to pipe");
}
