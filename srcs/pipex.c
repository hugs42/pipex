/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:15:11 by hugsbord          #+#    #+#             */
/*   Updated: 2021/12/07 12:31:20 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_find_path(t_data *data, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (cmd && access(cmd, X_OK) == 0)
	{
		data->path = ft_strdup(cmd);
		return (1);
	}
	while (data->env_path[i])
	{
		tmp = ft_strjoin(data->env_path[i], "/");
		data->path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(data->path, X_OK) == 0)
			return (1);
		free(data->path);
		i++;
	}
	return (0);
}

void	ft_exec_cmd2(t_data *data, char **env)
{
	dup2(data->fd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	close(data->fd[1]);
	if (ft_find_path(data, data->child[0]) == 0)
		ft_error("Pipex: command not found", data);
	if (execve(data->path, data->child, env) == -1)
		ft_error("Pipex", data);
}

void	ft_exec_cmd1(t_data *data, char **env)
{
	int		status;

	waitpid(-1, &status, 0);
	dup2(data->infile, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->infile);
	close(data->fd[0]);
	if (ft_find_path(data, data->parent[0]) == 0)
		ft_error("Pipex: command not found", data);
	if (execve(data->path, data->parent, env) == -1)
		ft_error("Pipex", data);
}

int	ft_pipex(t_data data, char **env)
{
	int	status;

	status = 0;
	pipe(data.fd);
	data.pid[0] = fork();
	if (data.pid[0] < 0)
		ft_error("Fork ", &data);
	if (data.pid[0] == 0)
		ft_exec_cmd1(&data, env);
	data.pid[1] = fork();
	if (data.pid[1] < 0)
		ft_error("Fork ", &data);
	if (data.pid[1] == 0)
		ft_exec_cmd2(&data, env);
	ft_close_fd(&data);
	ft_clear_data(&data);
	waitpid(data.pid[0], &status, 0);
	waitpid(data.pid[1], &status, 0);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		status;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(1);
	}
	if (ft_parser(&data, argv, env) == 0)
		ft_error("Pipex", &data);
	if (ft_pipex(data, env) != SUCCESS)
		return (0);
}
