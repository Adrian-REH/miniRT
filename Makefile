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
OBJ_DIRS     := obj/
CC          := gcc
CFLAGS      := -g -O3 -ffast-math -funroll-loops -march=native -flto -MMD
FSANITIZE   := 
RM          := rm -rf

INC         := inc/
LIB         := lib/
PRINTF_DIR  := $(LIB)ft_printf/
PRINTF      := $(PRINTF_DIR)libftprintf.a
MINILIBX_DIR := $(LIB)minilibx-linux/
MINILIBX    := $(MINILIBX_DIR)libmlx.a
LIBFT_DIR   := $(LIB)libft/
LIBFT       := $(LIBFT_DIR)libft.a

CYAN = \033[0;96m
DEF_COLOR = \033[0;49m
MINILIBXCC  := -I $(MINILIBX_DIR) -L $(MINILIBX_DIR) -lmlx
HEADER      := -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
FLAGSVISUAL := -L$(LIBFT_DIR) -lft -lm -lX11 -lXext  -lXt

SRC_FILES   =	src/lib/libcolor/calculate_attenuation.c \
				src/lib/libcolor/color_to_int.c \
				src/lib/libcolor/fill_color_by_int.c \
				src/lib/libcolor/get_color.c \
				src/lib/libcolor/illuminate_surface.c \
				src/lib/libcolor/int_to_color.c \
				src/lib/libcolor/mix_colors.c \
				src/lib/libcolor/normalize_color.c \
				src/lib/libcolor/rgb_to_color.c \
				src/lib/libcolor/set_color.c \
				src/lib/libcolor/specular_intensity.c \
				src/lib/libprojection/generate_ray.c \
				src/lib/libprojection/idxpixel.c \
				src/lib/libprojection/project3_to_pixel.c \
				src/lib/libvector3/calculate_intensity.c \
				src/lib/libvector3/distancev3.c \
				src/lib/libvector3/dotv3.c \
				src/lib/libvector3/hit_point.c \
				src/lib/libvector3/normalizev3.c \
				src/lib/libbrdf/reflect.c \
				src/lib/librandom/random_double.c \
				src/parser/parser_ambient.c \
				src/parser/parser_camera.c \
				src/parser/parser_light.c \
				src/parser/parser_cylinder.c \
				src/parser/parser_plane.c \
				src/parser/parser_polygon.c \
				src/parser/parser_obj.c \
				src/parser/parser_sphere.c \
				src/render/render_plane.c \
				src/render/render_sphere.c \
				src/render/render_polygon.c \
				src/render/render_cylinder.c \
				src/render/render_scene.c \
				src/object/ambient.c \
				src/object/camera.c \
				src/object/cylinder.c \
				src/object/light.c \
				src/object/plane.c \
				src/object/polygon.c \
				src/object/scene.c \
				src/object/sphere.c \
				src/main.c \

OBJ_DIRS := obj/src/lib/libcolor obj/src/lib/libprojection obj/src/lib/libvector3 obj/src/lib/libbrdf \
            obj/src/parser obj/src/render obj/src/object obj/src/lib/librandom

# Regla para crear los directorios de objetos
$(OBJ_DIRS):
	@mkdir -p $@

# Definir los objetos
OBJ := $(patsubst %.c,obj/%.o,$(SRC_FILES))

# Regla para compilar los archivos fuente en objetos
obj/%.o: %.c | $(OBJ_DIRS)
	@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

-include	${DEPS}
-include $(OBJ:.o=.d)
$(NAME):	$(OBJ)        
			@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(PRINTF) $(MINILIBXCC) $(FLAGSVISUAL) -o $(NAME)        
			@echo "$(GREEN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"


all:	$(OBJ_DIRS) makelibs
		@$(MAKE) $(NAME)

makelibs:    
		@$(MAKE) -C $(PRINTF_DIR)
		@$(MAKE) -C $(MINILIBX_DIR)
		@$(MAKE) -C $(LIBFT_DIR)

bonus :$(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)
	make fclean -C lib/libft
	@echo "$(CYAN) ✨ ¡CLEANED! ✨ $(DEF_COLOR)"

clean :
	@echo "$(CYAN) 🍩 ¡INIT CLEAN! 🍩 $(DEF_COLOR)"
	$(RM) $(OBJ) $(OBJ_DIRS) *.gcno *.gcda *.gcov *.html *.css
	make clean -C lib/libft

re : fclean all

norm :
	norminette | grep -i "error"

cov:
	gcov --object-directory=obj/lib lib/ft_sarrprint.c;
	@for src in $(SRCS); do \
		echo "Processing $$src"; \
		dir=$$(dirname "$$src"); \
		gcov --object-directory=obj/$$dir "$$src"; \
	done
	gcovr -r . --html --html-details -o coverage.html

.PHONY:     all clean fclean re bonus norm cov