/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:00:00 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/10 20:00:45 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error()
{
	perror("error");
	exit(EXIT_FAILURE);
}

void bad_format(void)
{
	ft_putstr_fd("\e[31mError: please specify you arguments.\e[0m\n", 2);
	ft_putstr_fd("Ex: FILE_1 ""COMMAND 1"" ""COMMAND 2"" FILE_2\n", 2);
	exit(EXIT_FAILURE);	
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	int	fd[2];
	int	pid;

	if (argc < 5)
		bad_format();
	args.argv = argv;
	parse_cmd(&args);
	args.filein_fd = open(argv[1], O_RDONLY);
	if (args.filein_fd < 0)
		error();
	args.fileout_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (args.fileout_fd < 0)
		error();
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid < 0)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(args.filein_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if(execve(get_path(args.cmd1[0], envp), args.cmd1, NULL) == -1)
			error();		
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(args.fileout_fd, STDOUT_FILENO);
		if(execve(get_path(args.cmd2[0], envp), args.cmd2, NULL) == -1)
			error();
	}
	// cleanup(&args);
}
