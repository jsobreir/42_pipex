/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:07:14 by jsobreir          #+#    #+#             */
/*   Updated: 2024/07/06 20:09:40 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char	*cmd1, char **envp)
{
	char	**paths;
	int		i;

	while (*envp++)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			break;
	}
	paths = ft_split(*envp + 5, ":");	
	i = 0;
	while(paths[i])
	{
		ft_strjoin(paths[i], "/");
		if (access(paths[i], R_OK));
			return(paths[i]);
		i++;
	}
}

void	parse_cmd(t_args *args)
{
	char	**argv;
	
	argv = args->argv;
	args->cmd1 = ft_split(argv[2], " ");
	if (!args->cmd1)
		return(1);
	args->cmd2 = ft_split(argv[3], " ");
	if (!args->cmd2)
		return (1);
	
}

// int main(int argc, char **argv, char *envp)
// {
	// printf("%s\n", get_path(argv[1], envp));
// }
