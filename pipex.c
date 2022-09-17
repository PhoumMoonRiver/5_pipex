/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njerasea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:26:28 by njerasea          #+#    #+#             */
/*   Updated: 2022/09/17 17:50:51 by njerasea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(char **av, int *ends, char **envp)
{
	int	fd_out;

	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 644);
	if (fd_out == -1)
		exit(0);
	dup2(fd_out, 1);
	dup2(ends[0], 0);
	close(ends[1]);
	execu(&av[3], envp);
}

void	child(char **av, int *ends, char **envp)
{
	int	fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
		exit(0);
	dup2(fd_in, 0);
	dup2(ends[1], 1);
	close(ends[0]);
	execu(&av[2], envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int	ends[2];
	int	i;
	
	if (ac != 5)
	{
		ft_putstr_fd("syntax error", 2);
		exit(0);
	}
	if (pipe(ends) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child(av, ends, envp);
	else if (pid > 0)
	{
		waitpid(pid, &i, 0);
		dprintf(2, "%d\n", WIFEXITED(i));
		dprintf(2, "%d\n", WEXITSTATUS(i));
		if (WEXITSTATUS(i) == 0) 
		{
        		//int es = WEXITSTATUS(i);
        		//dprintf(2 ,"Exit status was %d\n", es );
			//ดูเพิ่ม
			parent(av, ends, envp);
		}	
	}
}
