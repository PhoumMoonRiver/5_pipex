/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njerasea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:28:07 by njerasea          #+#    #+#             */
/*   Updated: 2022/09/18 18:34:21 by njerasea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> 

int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		num_word(char const *str, char c);
char	*ft_splitter(int *i, char const *str, int size);
char	**ft_prot(char const *s, char c, char **dest);
char	**ft_split(char const *s, char c);
char	*ft_get_path(char **cmd, char **envp);
void	ft_free2d(char **farg);
void	child(char **av, int *ends, char **envp);
void	parent(char **av, int *ends, char **envp);
void	execu(char **av, char **envp);
void	ft_putstr_fd(char *s, int fd);
char	*ft_wh_join(char **all_path, char **all_cmd, char **cmd);

#endif
