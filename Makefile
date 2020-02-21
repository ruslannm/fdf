# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgero <rgero@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/13 15:46:56 by rgero             #+#    #+#              #
#    Updated: 2020/02/21 17:16:28 by rgero            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
FW = -framework OpenGL -framework AppKit

SRC_PATH = srcs
SRC_NAME = main.c ft_read.c ft_draw.c ft_rotate.c ft_tab.c\
	ft_projection.c ft_image.c
SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME)) 

INCLUDES_PATH = includes libft
INCLUDES = $(addprefix -I, $(INCLUDES_PATH))

LIB_PATH = libft
LIB_NAME = libft.a

LIBMLX_PATH = minilibx_macos/
LIBMLX_NAME = libmlx.a

.PHONY: all clean fclean re libft libmlx

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)
	make -C $(LIBMLX_PATH)
	$(CC) $(OBJ) -L $(LIB_PATH)/ -lft -L $(LIBMLX_PATH)/ -lmlx	$(FW) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@/bin/mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

libft:
	make -C $(LIB_PATH)

libmlx:
	make -C $(LIBMLX_PATH)

clean:
	/bin/rm -rf $(OBJ_PATH)
	make -C $(LIB_PATH) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIB_PATH) fclean
	
re: fclean all
