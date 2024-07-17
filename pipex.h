/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:27 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/17 12:38:56 by jsobreir         ###   ########.fr       */
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
void	free_paths(char **paths, int i, int do_exit);

#endif