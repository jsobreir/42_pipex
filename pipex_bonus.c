/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:00:00 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/17 12:43:41 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	bad_format(void)
{
	ft_putstr_fd("\e[31mError: please specify you arguments.\e[0m\n", 2);
	ft_putstr_fd("Ex: FILE_1 ""COMMAND 1"" ""COMMAND 2"" FILE_2\n", 2);
	exit(EXIT_FAILURE);
}

void	parent_process(int pid, int *new_fd)
{
	waitpid(pid, NULL, 0);
	dup2(new_fd[0], STDIN_FILENO);
	close(new_fd[0]);
	close(new_fd[1]);
}

void	do_pipe(t_args *args, char **envp, int i)
{
	int	new_fd[2];
	int	pid;

	if (pipe(new_fd) == -1)
		error("pipe");
	pid = fork();
	if (pid < 0)
		error("fork");
	if (pid == 0)
	{
		if (i == 0)
			dup2(args->filein_fd, STDIN_FILENO);
		if (i == args->argc - 4)
			dup2(args->fileout_fd, STDOUT_FILENO);
		else
			dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[0]);
		close(new_fd[1]);
		if (execve(get_path(args->cmds[i][0], envp), args->cmds[i], NULL) == -1)
			error("execve2");
	}
	else
		parent_process(pid, new_fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	int		i;

	if (argc < 5)
		bad_format();
	args.filein_fd = open(argv[1], O_RDONLY);
	if ((args.filein_fd < 0))
		error("file");
	args.fileout_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (args.fileout_fd < 0)
		error("file");
	args.argc = argc;
	args.argv = argv;
	args.cmds = malloc((argc - 3) * sizeof(char **));
	parse_cmd(&args);
	i = -1;
	while (++i < argc - 3)
		do_pipe(&args, envp, i);
	close(args.filein_fd);
	close(args.fileout_fd);
}
