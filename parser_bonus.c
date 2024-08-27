/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:14 by jsobreir          #+#    #+#             */
/*   Updated: 2024/08/27 15:04:11 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!paths[i])
		{
			free_paths(paths);
			return (NULL);
		}
		if (access(paths[i], X_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (0);
}

void	parse_cmd(t_args *args)
{
	char	**argv;
	int		argc;
	int		i;

	argc = args->argc - 4;
	argv = args->argv;
	i = 0;
	while (i <= argc)
	{
		args->cmds[i] = ft_split(argv[i + 2], ' ');
		if (!args->cmds[i])
		{
			while (i--)
				free_paths(args->cmds[i]);
			free(args->cmds);
			error("Error: ", NULL, NULL, args);
		}
		i++;
	}
}

// int main (int argc, char **argv)
// {
// 	t_args	args;

// 	args.argc = argc;
// 	args.argv = argv;
// 	parse_cmd(&args);
// 	int	i = 0;
// 	argc -= 3;
// 	while (argc-- > 0)
// 	{
// 		i = 0;
// 		while (i < 2)
// 		{
// 			printf("%s  ", args.cmds[argc][i]);
// 			i++;
// 		}
// 		printf("\n");
// 	}
// }
