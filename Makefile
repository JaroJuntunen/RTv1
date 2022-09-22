# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 18:36:31 by jjuntune          #+#    #+#              #
#    Updated: 2022/09/22 13:30:54 by jjuntune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
INCLUDE_DIR = src/ build/libsdl2/include/
BUILD_DIR = build/

libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(BUILD_DIR)libsdl2/lib/libSDL2.a
libsdl2_cflags = `$(BUILD_DIR)libsdl2/bin/sdl2-config --cflags`
libsdl2_ldflags = `$(BUILD_DIR)libsdl2/bin/sdl2-config --libs`

FT_LIBRERY = src/libft/libft.a

SRC_FILES = $(addprefix $(SRC_DIR), main.c \
					vector_functions.c \
					vector_functions2.c \
					sphere_intersection.c \
					cylinder_intersection.c\
					cone_intersection.c\
					image_render.c \
					check_shadow.c \
					plane_intersection.c\
					read_map.c\
					shape_filler.c\
					shape_filler2.c\
					check_file_lines.c\
					check_lines_arguments.c\
					color_and_shading.c\
					calculate_shape_normals.c)

OBJCT_FILES = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_FILES:.c=.o))

NAME = RTv1

DEPENDENCY_FILES = $(subst $(SRC_DIR), $(BUILD_DIR), $(SRC_FILES:.c=.dep))
DEPENDENCY_FLAGS = -MT $(@) -MMD -MP -MF $(BUILD_DIR)$(*).dep

LD = gcc
LDFLAGS = -flto $(libsdl2_ldflags)
CC = gcc
CFLAGS = -O3 -flto -c -Wall -Werror -Wextra $(addprefix -I, $(INCLUDE_DIR))\
	$(libsdl2_cflags)
CPPFLAGS = -D_REENTRANT

all: $(NAME)

$(NAME): $(FT_LIBRERY) $(OBJCT_FILES) | $(BUILD_DIR) 
	@ $(LD) $(FT_LIBRERY) $(OBJCT_FILES) $(LDFLAGS) -o $(NAME)

$(OBJCT_FILES): $(libsdl2_lib)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR)%.dep
	@ $(CC) $(CFLAGS) $(CPPFLAGS) $(DEPENDENCY_FLAGS) -o $(@) $(<)

$(DEPENDENCY_FILES):

$(libsdl2_makefile):
	if test -d $(BUILD_DIR); then echo exists; else mkdir $(BUILD_DIR); fi
	cd libsdl2 && ./configure --prefix=$(abspath $(BUILD_DIR)libsdl2)\
		--disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(libsdl2_lib): $(libsdl2_makefile) | $(BUILD_DIR)
	$(MAKE) --directory=libsdl2 install

$(FT_LIBRERY):
	make -C src/libft/
	
clean:
	@ rm -f $(OBJCT_FILES)
	make -C src/libft/ clean

fclean:
	rm -f RTv1
	if test -f $(libsdl2_makefile); then $(MAKE) AUTOMAKE=: --directory=libsdl2\
		distclean; fi
	rm -rf $(BUILD_DIR)
	make -C src/libft/ fclean
	
re: fclean all

.PHONY: all clean fclean re

include $(wildcard $(DEPENDENCY_FILES))
