/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:14 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/12 14:58:53 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths, int i, int	do_exit)
{
	while(i--)
		free(paths[i]);
	free(paths);
	if (do_exit == 1)
		exit(EXIT_FAILURE);
	else
		return ;
}

char	*get_path(char	*cmd, char **envp)
{
	char	**paths;
	int		i;

	while (*envp++)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			break;
	}
	paths = ft_split(*envp + 5, ':');	
	if (!paths)
		exit(EXIT_FAILURE);
	i = 0;
	while(paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
			free_paths(paths, i, 1);
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!paths[i])
			free_paths(paths, i, 1);
		if (access(paths[i], R_OK) == 0)
			return (paths[i]);
		i++;
	}
	free_paths(paths, i, 0);
	return (0);
}

void	parse_cmd(t_args *args)
{
	char	**argv;
	
	argv = args->argv;
	args->cmd1 = ft_split(argv[2], ' ');
	if (!args->cmd1)
		exit(EXIT_FAILURE);
	args->cmd2 = ft_split(argv[3], ' ');
	if (!args->cmd2)
	{
		free(args->cmd1);
		exit(EXIT_FAILURE);
	}
}
