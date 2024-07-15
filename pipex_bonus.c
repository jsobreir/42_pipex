/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:00:00 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/15 14:09:08 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void bad_format(void)
{
	ft_putstr_fd("\e[31mError: please specify you arguments.\e[0m\n", 2);
	ft_putstr_fd("Ex: FILE_1 ""COMMAND 1"" ""COMMAND 2"" FILE_2\n", 2);
	exit(EXIT_FAILURE);	
}

void	do_pipe(t_args *args, char **envp, int i, int n_fd[2])
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error("pipe");
	if ((pid = fork()) < 0)
		error("fork");
	if (pid == 0)
	{
		if (i == 0)
			dup2(args->filein_fd, STDIN_FILENO);
		else
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(get_path(args->cmds[i][0], envp), args->cmds[i], NULL) == -1)
			error("execve2");
	}
	else
	{
		printf("Here3\n");
		n_fd[1] = fd[1];
		n_fd[0] = fd[0];
		close(fd[0]);
		close(fd[1]);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	int	fd[2];
	int	i;
	
	int	first_pipe_flag;
	first_pipe_flag = 1;
	args.filein_fd = open(argv[1], O_RDONLY);
	if ((args.filein_fd < 0))
		error("file");
	args.fileout_fd = open(argv[argc - 1], O_RDONLY | O_APPEND | O_WRONLY);
	if (args.fileout_fd < 0)
		error("file");
	args.argc = argc;
	args.argv = argv;
	args.cmds = malloc((argc - 3) * sizeof(char **));
	parse_cmd(&args);
	i = -1;
	while (++i < argc - 3)
		do_pipe(&args, envp, i, fd);
	i = -1;
	printf("Here4\n");
	dup2(args.fileout_fd, STDOUT_FILENO);
	if (execve(get_path(args.cmds[argc - 4][0], envp), args.cmds[argc - 4], NULL) == -1)
		error("execve2");
	}

/*
	int	fd[n_pipes][2]
	while (i < n_pipes)
		pipe(fd[i][2])
	fork()
	if (first process)
		dup2(filein, STDIN);
		dup2(fd[1], STDOUT);
		fork()
		execve
	
	else if (!first process && argc != last)
		dup2()
*/
