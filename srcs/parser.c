/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:56:32 by hugsbord          #+#    #+#             */
/*   Updated: 2021/12/07 12:30:51 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_get_path(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	return (ft_strdup(&env[i][5]));
}

char	**ft_path(char **env)
{
	char	*env_path;
	char	**path;

	env_path = ft_get_path(env);
	if (!env_path)
		return (NULL);
	path = ft_split(env_path, ':');
	if (!path)
	{
		free(env_path);
		return (NULL);
	}
	free(env_path);
	return (path);
}

char	**get_cmd(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	ft_parser(t_data *data, char **argv, char **env)
{
	data->env_path = ft_path(env);
	data->parent = ft_split(argv[2], ' ');
	data->child = ft_split(argv[3], ' ');
	data->infile = open(argv[1], O_RDONLY);
	data->outfile = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	data->cmd1 = ft_strdup(argv[2]);
	data->cmd2 = ft_strdup(argv[3]);
	if (data->infile < 0 || data->outfile < 0 || !data->cmd1
		|| !data->cmd2 || !data->child || !data->parent)
		return (0);
	return (SUCCESS);
}
