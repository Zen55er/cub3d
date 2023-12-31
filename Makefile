# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/25 10:10:00 by gacorrei          #+#    #+#              #
#    Updated: 2023/09/28 10:27:48 by tlemos-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
SRC			= main.c map.c validate_elements.c texture_validation.c \
			validate_map.c validate_map_edge.c mlx.c clean.c dda.c \
			movements.c minimap.c mlx_utils.c dda_utils_1.c dda_utils_2.c
LIBFT_DIR	= libft
LIBFT		= libft/libft.a
MLX_DIR		= minilibx-linux
MLX_INCLUDE = -Iminilibx-linux
CC			= @cc
# CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address,undefined
CFLAGS		= -Wall -Wextra -Werror -g
MLX_FLAGS 	= -L$(MLX_DIR) -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm

all:		$(NAME)

$(NAME):	$(SRC)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@$(MAKE) --no-print-directory -C $(MLX_DIR)
			$(CC) $(CFLAGS) $(^) $(MLX_FLAGS) -o $(@) $(LIBFT)

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