/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njerasea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:26:28 by njerasea          #+#    #+#             */
/*   Updated: 2022/09/18 17:53:26 by njerasea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_check(char **av, char **envp)
{
	char	**cmd;
	int		i;

	i = 2;
	while (i <= 3)
	{
		cmd = ft_split(av[i], 32);
		if ((access(ft_get_path(&av[i], envp), F_OK | R_OK) == -1))
		{
			write(2, "command not found: ", 19);
			ft_putstr_fd(cmd[0], 2);
			write(2, "\n", 1);
			ft_free2d(cmd);
		}
		else
			ft_free2d(cmd);
		i++;
	}
	return (0);
}

void	parent(char **av, int *ends, char **envp)
{
	int	fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		write(2, "No such file or directory", 25);
		exit(1);
	}
	dup2(fd_out, 1);
	dup2(ends[0], 0);
	close(ends[0]);
	close(ends[1]);
	execu(&av[3], envp);
}

void	child(char **av, int *ends, char **envp)
{
	int	fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
	{
		write(2, "No such file or directory", 25);
		exit(1);
	}
	dup2(fd_in, 0);
	dup2(ends[1], 1);
	close(ends[0]);
	execu(&av[2], envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		ends[2];

	if (ac != 5)
	{
		ft_putstr_fd("require: ./pipex infile cmd1 cmd2 outfile", 2);
		exit(1);
	}
	if (error_check(av, envp))
		exit(1);
	if (pipe(ends) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
		child(av, ends, envp);
	parent(av, ends, envp);
}
