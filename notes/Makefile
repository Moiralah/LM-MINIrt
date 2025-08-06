# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 15:46:22 by huidris           #+#    #+#              #
#    Updated: 2025/08/07 02:00:18 by huidris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minirt
FLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address

RTFILE = NULL
CC	= gcc

SRC_DIR	= .
SRC	= $(wildcard $(SRC_DIR)/*.c)

LIBFT	= ../libft
LIBFT_A	= ../libft/libft.a

MLX	= ../minilibx-linux
MLX_A	= ../minilibx-linux/libmlx.a

OBJ_DIR	= obj
OBJS	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LINKS	= -L $(LIBFT) -I minirt.h -lft -L $(MLX) -lmlx -lXext -lX11 -lm

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A) minirt.h
	$(CC) $(FLAGS) $(OBJS) $(LINKS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_A):
	make -C $(LIBFT)

$(MLX_A):
	make -C $(MLX)

all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) $(RTFILE)

.PHONY: all clean fclean re
