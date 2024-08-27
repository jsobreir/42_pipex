/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:27 by jsobreir          #+#    #+#             */
/*   Updated: 2024/08/27 11:32:51 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_args
{
	char	**argv;
	char	**cmd1;
	char	**cmd2;
	int		filein_fd;
	int		fileout_fd;
}			t_args;

char	*get_path(char	*cmd1, char **envp);
void	parse_cmd(t_args *args);
void	free_paths(char **paths);
void	error(char *error, char *after_msg, int *fd, t_args *args);
void	bad_format(void);
void	free_all(t_args *args);

#endif