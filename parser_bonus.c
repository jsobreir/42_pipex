/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:14 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/17 12:46:56 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_paths(char **paths, int i, int do_exit)
{
	while (i--)
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
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			break ;
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		exit(EXIT_FAILURE);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
			free_paths(paths, i, 1);
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!paths[i])
			free_paths(paths, i, 1);
		if (access(paths[i], X_OK) == 0)
			return (paths[i]);
		i++;
	}
	free_paths(paths, i, 1);
	return (0);
}

void	parse_cmd(t_args *args)
{
	char	**argv;
	char	***cmds;
	int		argc;
	int		i;

	cmds = args->cmds;
	argc = args->argc - 3;
	argv = args->argv;
	i = 0;
	while (i < argc)
	{
		cmds[i] = ft_split(argv[i + 2], ' ');
		if (!cmds[i])
		{
			while (cmds[i--])
				free(cmds[i]);
			free(cmds);
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
