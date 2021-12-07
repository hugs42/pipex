/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:48:31 by hugsbord          #+#    #+#             */
/*   Updated: 2021/12/07 12:27:11 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include "./../libft/libft.h"

#define SUCCESS 1

typedef struct s_data
{
	char	**child;
	char	**parent;
	char	*cmd1;
	char	*cmd2;
	int		infile;
	int		outfile;
	char	**env_path;
	int		fd[2];
	char	*path;
	pid_t	pid[2];
}	t_data;

int		main(int argc, char **argv, char **env);
void	ft_exec_cmd1(t_data *data, char **env);
void	ft_exec_cmd2(t_data *data, char **env);
int		ft_find_path(t_data *data, char *cmd);
char	**ft_get_cmd(char *argv);
char	**ft_path(char **env);
char	*ft_get_path(char **env);
int		ft_parser(t_data *data, char **argv, char **env);
void	*ft_free_double_tab(char **tab);
size_t	ft_count_word(char *s_bis, char c_sep);
size_t	ft_is_sep(char schar, char sep);
void	ft_close_fd(t_data *data);
void	ft_clear_data(t_data *data);
void	ft_clear_close(t_data *data);
void	ft_error(char *str, t_data *data);

#endif
