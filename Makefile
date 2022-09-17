# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njerasea <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 14:34:48 by njerasea          #+#    #+#              #
#    Updated: 2022/09/17 15:06:49 by njerasea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = ft_split.c\
       pipex.c\
       pipex_get_path.c\
       pipex_libft.c

CC = gcc -Wall -Wextra -Werror -std=c99 -g
RM = rm -rf

all: $(NAME)

$(NAME): 
	$(CC) $(SRCS) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
