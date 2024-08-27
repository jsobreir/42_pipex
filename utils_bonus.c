/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:55:38 by jsobreir          #+#    #+#             */
/*   Updated: 2024/08/27 15:08:27 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	exit(EXIT_FAILURE);
}

void	free_all(t_args *args)
{
	int	i;
	int	n;

	i = 0;
	while (i <= args->argc - 4)
	{
		n = 0;
		while (args->cmds[i][n] != NULL)
		{
			free(args->cmds[i][n]);
			n++;
		}
		free(args->cmds[i]);
		i++;
	}
	free(args->cmds);
	if (args->filein_fd)
		close(args->filein_fd);
	if (args->fileout_fd)
		close(args->fileout_fd);
}

void	bad_format(void)
{
	ft_putstr_fd("\e[31mError: please specify you arguments.\e[0m\n", 2);
	ft_putstr_fd("Ex: FILE_1 ""COMMAND 1"" ""COMMAND 2"" FILE_2\n", 2);
	exit(EXIT_FAILURE);
}
