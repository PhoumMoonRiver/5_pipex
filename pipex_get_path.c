/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njerasea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:05:20 by njerasea          #+#    #+#             */
/*   Updated: 2022/09/17 18:50:06 by njerasea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	execu(char **av, char **envp)
{
	char	**cmd;
	char	*execu_path;

	cmd = ft_split(*av, 32);
	if(access(*av, F_OK | R_OK) == 0)
		execve(*av, cmd, envp);
	execu_path = ft_get_path(av, envp);
	dprintf(2, "This is execu ==> [%p][%s]\n", execu_path, execu_path);
	dprintf(2, "This is av ==> [%p][%s]\n", av[0], av[0]);
	if (execve(execu_path, cmd, envp) == -1)
	{
		ft_putstr_fd("command not found plase try again!!", 2);
		ft_free2d(cmd);
		exit(1);
	}
	free(execu_path);
	ft_free2d(cmd);
}

void	ft_free2d(char **farg)
{
	size_t	i;

	i = 0;
	if (!farg || !farg[i])
		return ;
	while (farg[i])
	{
		free(farg[i]);
		i++;
	}
	free(farg);
}

char	*ft_get_path(char **cmd, char **envp)
{
	char	**all_path;
	char	**all_cmd;
	char	*get_path;
	char	*execu;
	int	i;

	i = 0;
	all_cmd = ft_split(*cmd, 32);
	while(ft_strncmp(*envp++, "PATH", 4) != 0)
	all_path = ft_split(*envp + 5, ':');
	while(all_path[i])
	{
		get_path = ft_strjoin(all_path[i], "/");
		execu = ft_strjoin(get_path, *all_cmd);
		free(get_path);
		if(access(execu, F_OK | R_OK) == 0)
		{
			ft_free2d(all_cmd);
			ft_free2d(all_path);
			return(execu);
		}
		free(execu);
		i++;
	}
	ft_free2d(all_path);
	ft_free2d(all_cmd);
	return (*cmd);
}
