/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:00:00 by jsobreir          #+#    #+#             */
/*   Updated: 2024/08/27 14:29:49 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent_process(int pid, int *new_fd)
{
	(void)pid;
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
		error("pipe", NULL, new_fd, args);
	pid = fork();
	if (pid < 0)
		error("fork", NULL, new_fd, args);
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
			error("zsh: command not found: ", args->cmds[i][0], NULL, args);
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
		error("file", NULL, NULL, &args);
	args.fileout_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (args.fileout_fd < 0)
		error("file", NULL, NULL, &args);
	args.argc = argc;
	args.argv = argv;
	args.cmds = malloc((argc - 3) * sizeof(char **));
	if (!args.cmds)
		error("Error:", NULL, NULL, &args);
	parse_cmd(&args);
	i = -1;
	while (++i < argc - 3)
		do_pipe(&args, envp, i);
	free_all(&args);
}
