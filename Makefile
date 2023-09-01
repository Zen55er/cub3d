# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/25 10:10:00 by gacorrei          #+#    #+#              #
#    Updated: 2023/09/01 14:47:21 by gacorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
SRC			= map.c clean.c texture_validation.c
LIBFT_DIR	= libft
LIBFT		= libft/libft.a
MLX_DIR		= minilibx-linux
MLX_INCLUDE = -Imlx_linux
CC			= @cc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address,undefined
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

good:		all
			@for file in ./maps/good/*; do \
				echo "$$file"; \
				./$(NAME) $$file; \
			done

wrong:		all
			@for file in ./maps/wrong/*; do \
				echo "$$file"; \
				./$(NAME) $$file; \
			done

re:			fclean all

.PHONY:		all clean fclean re