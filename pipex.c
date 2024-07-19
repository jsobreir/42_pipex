/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:42:29 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/19 17:27:03 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error, char *after_msg, int *fd, t_args *args)
{
	ft_putstr_fd(error, 2);
	if (after_msg != 0)
		ft_putstr_fd(after_msg, 2);
	ft_putchar_fd('\n', 2);
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (args->filein_fd)
		close(args->filein_fd);
	if (args->fileout_fd)
		close(args->fileout_fd);
	if (args->cmd1)
		free_paths(args->cmd1, 2, 0);
	if (args->cmd2)
		free_paths(args->cmd2, 2, 1);
	exit(0);
}

void	bad_format(void)
{
	ft_putstr_fd("\e[31mError: please specify you arguments.\e[0m\n", 2);
	ft_putstr_fd("Ex: FILE_1 ""COMMAND 1"" ""COMMAND 2"" FILE_2\n", 2);
	exit (0);
}

static void	exec(int *pid, t_args *args, int *fd, char **envp)
{
	if (pid[0] == 0)
	{
		close(fd[0]);
		dup2(args->filein_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(get_path(args->cmd1[0], envp), args->cmd1, envp) == -1)
			error("zsh: command not found: ", args->argv[2], fd, args);
	}
	if (pid[1] == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(args->fileout_fd, STDOUT_FILENO);
		if (execve(get_path(args->cmd2[0], envp), args->cmd2, envp) == -1)
			error("zsh: command not found: ", args->argv[2], fd, args);
	}
}

void	free_all(t_args *args)
{
	free_paths(args->cmd1, 2, 0);
	free_paths(args->cmd2, 2, 1);
	close(args->filein_fd);
	close(args->fileout_fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	int		fd[2];
	int		pid[2];

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
	pid[0] = fork();
	if (pid[0] < 0)
		error("error: fork", 0, fd, &args);
	pid[1] = fork();
	if (pid[1] < 0)
		error("error: fork", 0, fd, &args);
	exec(pid, &args, fd, envp);
	free_all(&args);
	return (0);
}
