# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgero <rgero@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/13 15:46:56 by rgero             #+#    #+#              #
#    Updated: 2020/02/16 17:27:44 by rgero            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
FRAMEWORKS = -framework OpenGL -framework AppKit

SRC_PATH = ./srcs/
SRC_NAME = main.c ft_read.c ft_draw.c
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_PATH = ./srcs/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))cd 

INC_PATH = ./libft/ ./minilibx_macos/ ./includes
INC = $(addprefix -I, $(INC_PATH))

#LIB_PATH = libft/
#LIB_NAME = libft.a

INCLUDES = libft/libft.a minilibx_macos/libmlx.a

.PHONY: all clean fclean re

all:
	make -C libft/ all
	make -C minilibx_macos/ all
	$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(INC) $(INCLUDES) $(FRAMEWORKS)

#all: $(NAME)

#$(NAME): $(LIB_PATH)$(LIB_NAME) $(OBJ_NAME)
#	$(CC) -o $(NAME)  $(OBJ_NAME) -L $(LIB_PATH) -lft

%.o: %.c $(NAME).h
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@  -c $<

#$(LIB_PATH)$(LIB_NAME):
#	make -C $(LIB_PATH)

#clean:
#	/bin/rm -f $(OBJ)
#	make -C $(LIB_PATH) clean
#fclean: clean
#	/bin/rm -f $(NAME)
#	/bin/rm -f $(LIB_PATH)$(LIB_NAME)
	
#re: fclean all
