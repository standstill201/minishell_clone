/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:08:42 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/21 09:44:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../include/execute.h"
#include <stdio.h> // must delete!

void	is_directory(t_cmd *node)
{
	struct stat	sb;

	if (stat(node->cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
		minishell_error("is a directory"); // not error!
}

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

	if (ft_strchr(node->cmd, '/'))
		minishell_error(node->cmd);
	command = ft_strjoin("/", node->cmd);
	envp = get_environ(environ);
	path = find_path(command, envp);
	printf("command: [%s], path: [%s]\n", command, path);
	if (path == NULL || ft_strlen(node->cmd) == 0)
		return (0);
	if (execve(path, node->args, envp) == -1)
	{
		printf("EXECVE FAILED\n");
		free(command);
		free(path);
		// free(args);
	}
	return (0);
}

// env에 대한 정보가 필요하다.
// return value에 대한 고민
int	execute_builtin(t_cmd *node, t_env *environ)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
	{
		ft_putstr_fd("PROD: ECHO EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "cd", 3) == 0)
		exit(1);
	else if (ft_strncmp(node->cmd, "pwd", 4) == 0)
	{
		ft_putstr_fd("PROD: PWD EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "export", 7) == 0)
	{
		ft_putstr_fd("PROD: EXPORT EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "unset", 6) == 0)
	{
		ft_putstr_fd("PROD: UNSET EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "env", 4) == 0)
	{
		ft_putstr_fd("PROD: ENV EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "exit", 5) == 0)
	{
		ft_putstr_fd("PROD: EXIT EXECUTED\n", 1);
		exit(1);
	}
	return (ret);
}

// need to add FUNCTION_GUARD
static int	pipeline(t_cmd *node, t_env *environ)
{
	int		pfd[2];
	int		status;
	pid_t	pid;

	pipe(pfd);
	pid = fork();
	if (pid == -1)
		minishell_error("fork error");
	else if (pid == 0)
	{
		close(pfd[READ_END]);
		// 음... 애초에 0과 1로 세팅해준다면...?
		if (node->fd_out == -2)
			node->fd_out = STDOUT_FILENO;
		dup2(pfd[WRITE_END], node->fd_out);
		close(pfd[WRITE_END]);
		// need to check error message
		if (ft_strchr(node->cmd, '/'))
			is_directory(node);
		if (!execute_builtin(node, environ))
			if (!execute_command(node, environ))
				// error 시 연결리스트 해제 필요.
				command_not_found(node->cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(pfd[WRITE_END]);
		if (node->fd_in == -2)
			node->fd_in = STDIN_FILENO;
		dup2(pfd[READ_END], node->fd_in);
		close(pfd[READ_END]);
	}
	return (status);
}

void	execute(t_cmd *root, t_env *environ)
{
	t_cmd	*node;
	pid_t	pid;
	int		status;

	pid = fork();
	node = root;
	if (pid == -1)
		minishell_error("fork error");
	else if (pid == 0)
	{
		while (node->next != NULL)
		{
			// should get return value
			pipeline(node, environ);
			node = node->next;
		}
		// need to check error message
		// 극혐 구조! 구조에 대한 고민을 하자.
		if (ft_strchr(node->cmd, '/'))
			is_directory(node);
		if (!execute_builtin(node, environ))
			if (!execute_command(node, environ))
				command_not_found(node->cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (ft_strncmp(node->cmd, "cd", 3) == 0)
			chdir(ft_cd_master(node, environ));
	}
	// cd 부모 프로세스에 전달할 수 있는 방법 고민
//	return (WEXITSTATUS(status));
}
*/
