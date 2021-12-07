/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:58:34 by hugsbord          #+#    #+#             */
/*   Updated: 2021/12/07 12:26:48 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(char *str, t_data *data)
{
	ft_clear_close(data);
	if (errno)
		perror(str);
	else
		ft_putstr_fd(str, 2);
	exit(1);
}

void	ft_clear_close(t_data *data)
{
	ft_clear_data(data);
	ft_close_fd(data);
}

void	ft_clear_data(t_data *data)
{
	if (data->env_path)
		ft_free_dtab(data->env_path);
	if (data->child)
		ft_free_dtab(data->child);
	if (data->parent)
		ft_free_dtab(data->parent);
	if (data->cmd1)
		free(data->cmd1);
	if (data->cmd2)
		free(data->cmd2);
}

void	ft_close_fd(t_data *data)
{
	close(data->infile);
	close(data->outfile);
	close(data->fd[0]);
	close(data->fd[1]);
}
