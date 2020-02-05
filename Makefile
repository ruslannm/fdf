# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgero <rgero@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/13 15:46:56 by rgero             #+#    #+#              #
#    Updated: 2020/02/05 18:46:31 by rgero            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_PATH = ./
SRC_NAME = main.c ft_move_tetra.c ft_sqrt.c ft_fill_matrix.c \
	ft_dancing_links.c	ft_stack_pop.c ft_stack_push.c \
	ft_move_same_bits.c ft_move_same_letter.c \
	ft_create_blank_line.c ft_add_dummy.c ft_delete_dl.c \
	ft_strnew_char.c ft_size_tetra.c ft_init_header.c \
	ft_check_links.c ft_lstaddback.c \
	ft_row_for_search.c ft_delete_root.c ft_del_content.c \
	ft_get_buff.c

OBJ_PATH = ./
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

INC_PATH = ./libft/
INC = $(addprefix -I, $(INC_PATH))

LIB_PATH = libft/
LIB_NAME = libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB_PATH)$(LIB_NAME) $(OBJ_NAME)
	$(CC) -o $(NAME)  $(OBJ_NAME) -L $(LIB_PATH) -lft

%.o: %.c $(NAME).h
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@  -c $<

$(LIB_PATH)$(LIB_NAME):
	make -C $(LIB_PATH)

clean:
	/bin/rm -f $(OBJ)
	make -C $(LIB_PATH) clean
fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB_PATH)$(LIB_NAME)
	
re: fclean all
