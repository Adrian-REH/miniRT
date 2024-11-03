# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 00:53:49 by adherrer          #+#    #+#              #
#    Updated: 2024/03/30 23:52:35 by adherrer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = libft/
LIBFT_NAME = libft.a
CC = gcc
PACK = ar rcs
FRM = rm -rf
CFLAGS = -Wall -Wextra -Werror -I.
CORE_FILES = \
	ft_printf.c 	\
	ft_strnbr_base.c \

CORE_OBJS = $(patsubst %.c, %.o, $(CORE_FILES))
LIBFT_LIB = $(addprefix $(LIBFT), $(LIBFT_NAME))
$(NAME): $(CORE_OBJS)
	@make all -C $(LIBFT)
	@mv $(LIBFT_LIB) $(NAME) ||:
	$(PACK) $(NAME) $(CORE_OBJS)
all: $(NAME)
clean:
	@make clean -C $(LIBFT)
	$(FRM) $(CORE_OBJS)
fclean: clean
	@make fclean -C $(LIBFT)
	$(FRM) $(NAME)
re: fclean all
.PHONY: re clean fclean all