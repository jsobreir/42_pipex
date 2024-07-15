/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:27 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/12 13:49:24 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#define _POSIX_SOURCE

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"

typedef struct s_args
{
	char	**argv;
	int		argc;
	char	***cmds;
	int		filein_fd;
	int		fileout_fd;
}			t_args;

char	*get_path(char	*cmd1, char **envp);
void	parse_cmd(t_args *args);
void	free_paths(char **paths, int i, int	do_exit);

#endif