# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyou </var/mail/jyou>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/22 19:14:13 by jyou              #+#    #+#              #
#    Updated: 2020/07/22 22:58:19 by jyou             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CLAGS = -Wall -Werror -Wextra
TARGET = bsq
OBJECTS = main.c scan.c valid.c find.c stdin.c print.c util.c

$(TARGET) : $(OBJECTS)
	$(CC) $(CLFLAGS) -o $@ $^

fclean:
	rm -rf *.o $(TARGET)
