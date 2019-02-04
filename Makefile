# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmartynu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/02 08:25:30 by vmartynu          #+#    #+#              #
#    Updated: 2018/08/15 09:24:03 by vmartynu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	RT
LIBFT	=	-L ./libft/Libft/ -lft
INC		=	-I ./inc/ -I ./SDL/SDL2.framework/Headers\
			-I ./SDL/SDL2_image.framework/Headers\
			-I ./SDL/SDL2_ttf.framework/Headers
FRM		=	-F ./SDL/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework OpenCL
GCC		=	gcc -Wall -Wextra -Werror -O3
SRC		=	./src/pars/check_in.c \
			./src/free_everything_left.c \
			./src/poll_events_additional.c \
			./src/poll_events.c \
			./src/menu/obj_intersection_composed.c \
			./src/menu/obj_intersection_other_simple.c \
			./src/menu/obj_intersection_mandator.c \
			./src/menu/obj_intersection_box.c \
			./src/init_buffs.c \
			./src/cl_errors.c \
			./src/pars/parse_object_file.c \
			./src/pars/get_sphere_obj.c \
			./src/pars/get_obj_data.c \
			./src/pars/init_triangle.c \
			./src/pars/read_obj_file.c \
			./src/pars/init_typical_obj.c \
			./src/pars/ft_arrange_tetragon.c \
			./src/init_cl.c \
			./src/menu/vector_operation_1.c \
			./src/menu/vector_operation_2.c \
			./src/pars/precalc_params.c \
			./src/pars/init_other_simple_objects_2.c \
			./src/pars/init_mandatory_objects.c \
			./src/pars/init_other_simple_objects.c \
			./src/pars/init_composed_objects.c \
			./src/pars/parse_functions_3.c \
			./src/pars/check_tags.c \
			./src/pars/parse_functions_2.c \
			./src/pars/parse_scene_lights.c \
			./src/pars/parse_functions.c \
			./src/pars/parse_scene_objects.c \
			./src/pars/read_scene_from_file.c \
			./src/init_int_array.c  \
			./src/pars/parse_functions_double_5.c \
			./src/pars/parse_functions_double_4.c \
			./src/pars/parse_functions_double_3.c \
			./src/pars/parse_functions_double_2.c \
			./src/pars/parse_functions_double.c \
			./src/main.c \
			./src/putpixel.c \
			./src/init_sdl.c \
			./src/render.c \
			./src/loop.c \
			./src/menu/ft_create_menu.c \
			./src/menu/ft_menu_button_action.c \
			./src/cartoon.c \
			./src/menu/obj_intersection_add_2.c \
			./src/menu/ft_choose_obj.c \
			./src/menu/obj_intersection_add_1.c \
			./src/menu/ft_add_color_effect.c \
			./src/menu/init_buttons.c \
			./src/menu/ft_add_menu.c \
			./src/menu/ft_change_obj_params.c \
			./src/menu/ft_change_obj_mater.c \
			./src/pars/object_alloc.c \
			./src/menu/ft_add_texts.c \
			./src/menu/solve_quart_eq1.c \
			./src/menu/solve_quart_eq2.c \
			./src/upload_textures_and_bump.c

OBJ		=	$(SRC:.c=.o) 

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/Libft/
	$(GCC)  -o $(NAME) $(OBJ) $(LIBFT) $(FRM)
%.o : %.c ./inc/rt.h
	 $(GCC) -c  $< -o $@ $(INC)
clean:
	rm -f $(OBJ)
	make clean -C libft/Libft/
fclean: clean
	rm -f $(NAME)
	make fclean -C libft/Libft/
re: fclean all
