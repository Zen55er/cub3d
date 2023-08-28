# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/25 10:10:00 by gacorrei          #+#    #+#              #
#    Updated: 2023/08/28 14:29:11 by gacorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
SRC			= map.c clean.c
LIBFT_DIR	= libft
LIBFT		= libft/libft.a
MLX_DIR		= minilibx-linux
MLX_INCLUDE = -Imlx_linux
CC			= @cc
CFLAGS		= -Wall -Wextra -Werror -g3 -O3 -fsanitize=address,undefined
MLX_FLAGS 	= -L$(MLX_LIB_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

all:		$(NAME)

$(NAME):	$(SRC)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@$(MAKE) --no-print-directory -C $(MLX_DIR)
			$(CC) $(CFLAGS) $(^) -o $(@) $(LIBFT)

clean:
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
			@$(MAKE) --no-print-directory -C $(MLX_DIR) clean

fclean:		clean
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
			@$(MAKE) --no-print-directory -C $(MLX_DIR) clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re