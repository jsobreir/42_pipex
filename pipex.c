/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:42:29 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/06 19:16:07 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

// ./pipex infile "command_1" "command_2" outfile 
int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	int	fd[2];
	int	pid;

	args.argv = argv;
	init_pipex(&args);
	parse_cmd(&args);
	parse_files();
	
	args.filein = open(argv[0], O_RDONLY);
	if (!args.filein)
		return(1);
	args.fileout = open(argv[4], O_WRONLY);
	if (!args.fileout)
		return(1);
	// ft_exec();
	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(args.filein, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve(get_path(args.cmd1, envp), args.cmd1, NULL);
		close(fd[1]);
		// execve(path, commands, NULL);
	}
	else
	{
		char buffer[1];
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		read(STDIN_FILENO, buffer, 1);
		printf("%s", buffer);
	}
}