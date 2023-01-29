# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 13:48:16 by hed-dyb           #+#    #+#              #
#    Updated: 2023/01/27 10:59:44 by hed-dyb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


all : client server

client : client.c minitalk.h functions.c
	cc -Wall -Werror -Wextra client.c functions.c -o client
	
server : server.c minitalk.h functions.c
	cc -Wall -Werror -Wextra server.c functions.c -o server
	
clean :
	rm -rf client server

fclean :
	rm -rf client server

re : fclean all

.PHONY : clean fclean all