/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njerasea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:05:20 by njerasea          #+#    #+#             */
/*   Updated: 2022/09/18 18:35:37 by njerasea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_wh_join(char **all_path, char **all_cmd, char **cmd)
{
	int		i;
	char	*execu;
	char	*get_path;

	i = 0;
	while (all_path[i])
	{
		get_path = ft_strjoin(all_path[i], "/");
		execu = ft_strjoin(get_path, *all_cmd);
		free(get_path);
		if (access(execu, F_OK | R_OK) == 0)
		{
			ft_free2d(all_cmd);
			return (execu);
		}
		free(execu);
		i++;
	}
	ft_free2d(all_path);
	ft_free2d(all_cmd);
	return (*cmd);
}

void	execu(char **av, char **envp)
{
	char	**cmd;

	cmd = ft_split(*av, 32);
	if (access(*av, F_OK | R_OK) == 0)
	{
		ft_free2d(cmd);
		execve(*av, cmd, envp);
	}
	execve(ft_get_path(av, envp), cmd, envp);
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
	int		i;

	i = 0;
	all_cmd = ft_split(*cmd, 32);
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	all_path = ft_split(envp[i] + 5, ':');
	return (ft_wh_join(all_path, all_cmd, cmd));
}
