# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 02:54:59 by adherrer          #+#    #+#              #
#    Updated: 2024/11/02 00:24:44 by adherrer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        := miniRT
SRC_DIR     := src/
OBJ_DIR     := obj/
CC          := gcc
CFLAGS      := -g -O3 -ffast-math -funroll-loops -march=native -flto -fsanitize=address,leak
FSANITIZE   := 
RM          := rm -f

INC         := inc/
LIB         := lib/
PRINTF_DIR  := $(LIB)ft_printf/
PRINTF      := $(PRINTF_DIR)libftprintf.a
MINILIBX_DIR := $(LIB)minilibx-linux/
MINILIBX    := $(MINILIBX_DIR)libmlx.a
LIBFT_DIR   := $(LIB)libft/
LIBFT       := $(LIBFT_DIR)libft.a

MINILIBXCC  := -I $(MINILIBX_DIR) -L $(MINILIBX_DIR) -lmlx
HEADER      := -I$(INC) -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
FLAGSVISUAL := -L$(LIBFT_DIR) -lft -lm -lX11 -lXext  -lXt

SRC_FILES   =   main

SRC         =   $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         =   $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS        =   $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

OBJF        =   .cache_exists


all:	makelibs
		@$(MAKE) $(NAME)

makelibs:    
		@$(MAKE) -C $(PRINTF_DIR)
		@$(MAKE) -C $(MINILIBX_DIR)
		@$(MAKE) -C $(LIBFT_DIR)

-include	${DEPS}
$(NAME):	$(OBJ)        
			@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(PRINTF) $(MINILIBXCC) $(FLAGSVISUAL) -o $(NAME)        
			@echo "👉 $(BLUE)$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(PRINTF) $(MINILIBXCC) $(FLAGSVISUAL) -o $(NAME)$(DEF_COLOR)"
			@echo "$(GREEN)✨ FDF compiled!$(DEF_COLOR)"

bonus:      
			@$(MAKE) all
            
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) -MMD -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)
	@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"    

$(MINILIBX):
	@make -C $(MINILIBX_DIR)
	@echo "$(GREEN)Minilibx compiled!$(DEF_COLOR)"            

clean:
			@make clean -sC $(PRINTF_DIR)
			@echo "$(CYAN)ft_printf object and dependency files cleaned.$(DEF_COLOR)"
			@make clean -C $(MINILIBX_DIR)
			@echo "$(CYAN)Minilibx object files cleaned.$(DEF_COLOR)"    
			@make clean -C $(LIBFT_DIR)
			@echo "$(CYAN)Libft object files cleaned.$(DEF_COLOR)"
			$(RM) -rf $(OBJ_DIR)
			@echo "$(CYAN)Fdf object files cleaned!$(DEF_COLOR)"

fclean:		clean
			$(RM) -f $(NAME)
			@echo "$(CYAN)Fdf executable files cleaned!$(DEF_COLOR)"
			$(RM) -f $(MINILIBX_DIR)libmlx.a
			@echo "$(CYAN)libmlx.a lib cleaned!$(DEF_COLOR)"            
			$(RM) -f $(LIBFT_DIR)libft.a
			@echo "$(CYAN)libft.a lib cleaned!$(DEF_COLOR)"

re:			fclean 
			@$(MAKE)    
			@echo "$(GREEN)Cleaned and rebuilt everything for Fdf!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INC) | grep -v Norme -B1 || true

.PHONY:     all clean fclean re