/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:42:29 by jsobreir          #+#    #+#             */
/*   Updated: 2024/08/27 14:02:05 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error, char *after_msg, int *fd, t_args *args)
{
	ft_putstr_fd(error, 2);
	if (after_msg != 0)
		ft_putstr_fd(after_msg, 2);
	ft_putchar_fd('\n', 2);
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
	if (args->filein_fd && args->filein_fd != -1)
		close(args->filein_fd);
	if (args->fileout_fd && args->fileout_fd != -1)
		close(args->fileout_fd);
	if (args->cmd1)
		free_paths(args->cmd1);
	if (args->cmd2)
		free_paths(args->cmd2);
	exit(EXIT_FAILURE);
}

static void	first_child(t_args *args, int *fd, char **envp)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		error("error: fork", 0, fd, args);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(args->filein_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(get_path(args->cmd1[0], envp), args->cmd1, envp) == -1)
			error("zsh: command not found: ", args->argv[2], fd, args);
	}
}

static void	second_child(t_args *args, int *fd, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error("error: fork", 0, fd, args);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(args->fileout_fd, STDOUT_FILENO);
		if (execve(get_path(args->cmd2[0], envp), args->cmd2, envp) == -1)
			error("zsh: command not found: ", args->argv[3], fd, args);
	}
	else
		wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	int		fd[2];

	fd[0] = 0;
	fd[1] = 0;
	if (argc != 5)
		bad_format();
	args.argv = argv;
	parse_cmd(&args);
	args.filein_fd = open(argv[1], O_RDONLY);
	if (args.filein_fd < 0)
		error("zsh: No such file or directory: ", argv[1], fd, &args);
	args.fileout_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (args.fileout_fd < 0)
		error("zsh: No such file or directory: ", argv[4], fd, &args);
	if (pipe(fd) == -1)
		error("error: pipe", 0, fd, &args);
	first_child(&args, fd, envp);
	wait(NULL);
	close(fd[1]);
	second_child(&args, fd, envp);
	close(fd[0]);
	free_all(&args);
	return (0);
}
