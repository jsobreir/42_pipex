/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:29:43 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/24 22:04:07 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	bad_format(void)
{
	ft_putstr_fd("\e[31mError: please specify you arguments.\e[0m\n", 2);
	ft_putstr_fd("Ex: FILE_1 ""COMMAND 1"" ""COMMAND 2"" FILE_2\n", 2);
	exit(EXIT_FAILURE);
}

void	free_all(t_args *args)
{
	free_paths(args->cmd1);
	free_paths(args->cmd2);
	close(args->filein_fd);
	close(args->fileout_fd);
}
