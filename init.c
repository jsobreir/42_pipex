/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:01 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/06 16:03:53 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_args *args)
{
	args->filein = malloc(ft_strlen(args->argv[1]) * sizeof(char));
	if(!args->filein)
		exit(EXIT_FAILURE);
	args->fileout = malloc(ft_strlen(args->argv[4]) * sizeof(char));
	if(!args->fileout)
		return(free(args->filein), exit(EXIT_FAILURE));
		
}