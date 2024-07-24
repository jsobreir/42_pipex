/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:14 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/24 19:20:07 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	while (i--)
		free(paths[i]);
	free(paths);
}

char	*get_path(char	*cmd, char **envp)
{
	char	**paths;
	int		i;

	while (*envp++)
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			break ;
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		exit(EXIT_FAILURE);
	i = 0;
	while (paths[i++])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!paths[i])
		{
			free_paths(paths);
			return (NULL);
		}
		if (access(paths[i], R_OK) == 0)
			return (paths[i]);
	}
	return (NULL);
}

void	parse_cmd(t_args *args)
{
	char	**argv;

	argv = args->argv;
	args->filein_fd = 0;
	args->fileout_fd = 0;
	args->cmd1 = ft_split(argv[2], ' ');
	if (!args->cmd1)
		error("Error: ", NULL, NULL, args);
	args->cmd2 = ft_split(argv[3], ' ');
	if (!args->cmd2)
		error("Error: ", NULL, NULL, args);
}
