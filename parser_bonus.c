/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:14 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/10 18:45:38 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths, int i)
{
	while(i--)
		free(paths[i]);
	free(paths);
	exit(EXIT_FAILURE);
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
		if (!ft_strjoin(paths[i], "/"))
			free_paths(paths, i);
		if (!ft_strjoin(paths[i], cmd))
			free_paths(paths, i);
		if (access(paths[i], R_OK) == 0)
			return (paths[i]);
		i++;
	}
	free_paths(paths, i);
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
