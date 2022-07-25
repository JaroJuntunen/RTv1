# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 18:36:31 by jjuntune          #+#    #+#              #
#    Updated: 2022/07/25 14:46:20 by jjuntune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

src_dir = src/
include_dirs = src/ build/libsdl2/include/
build_dir = build/

libsdl2_makefile = libsdl2/Makefile
libsdl2_lib = $(build_dir)libsdl2/lib/libSDL2.a
libsdl2_cflags = `$(build_dir)libsdl2/bin/sdl2-config --cflags`
libsdl2_ldflags = `$(build_dir)libsdl2/bin/sdl2-config --libs`

FT_LIBRERY = src/libft/libft.a

src_files = $(addprefix $(src_dir), main.c \
					vector_functions.c \
					sphere_intersection.c \
					cylinder_intersection.c\
					cone_intersection.c\
					Image_render.c \
					check_shadow.c \
					plane_intersection.c)

obj_files = $(subst $(src_dir), $(build_dir), $(src_files:.c=.o))

NAME = RTv1

dependency_files = $(subst $(src_dir), $(build_dir), $(src_files:.c=.dep))
dependency_flags = -MT $(@) -MMD -MP -MF $(build_dir)$(*).dep

LD = gcc
LDFLAGS = -flto $(libsdl2_ldflags)
CC = gcc
CFLAGS = -O3 -flto -c -Wall -Werror -Wextra $(addprefix -I, $(include_dirs)) $(libsdl2_cflags)
CPPFLAGS = -D_REENTRANT

all: $(NAME)

$(NAME): $(FT_LIBRERY) $(obj_files) | $(build_dir) 
	@ $(LD) $(FT_LIBRERY) $(obj_files) $(LDFLAGS) -o $(NAME) -fsanitize=address

$(obj_files): $(libsdl2_lib)

$(build_dir):
	mkdir $(build_dir)

$(build_dir)%.o: $(src_dir)%.c
$(build_dir)%.o: $(src_dir)%.c | $(build_dir)%.dep
	@ $(CC) $(CFLAGS) $(CPPFLAGS) $(dependency_flags) -o $(@) $(<) -fsanitize=address

$(dependency_files):

$(libsdl2_makefile):
	if test -d $(build_dir); then echo exists; else mkdir $(build_dir); fi
	cd libsdl2 && ./configure --prefix=$(abspath $(build_dir)libsdl2) --disable-shared --disable-video-wayland
	$(MAKE) --directory=libsdl2

$(libsdl2_lib): $(libsdl2_makefile) | $(build_dir)
	$(MAKE) --directory=libsdl2 install

$(FT_LIBRERY):
	make -C src/libft/
	
clean:
	@ rm -f $(obj_files)
	make -C src/libft/ clean

fclean:
	rm -f RTv1
	if test -f $(libsdl2_makefile); then $(MAKE) AUTOMAKE=: --directory=libsdl2 distclean; fi
	rm -rf $(build_dir)
	make -C src/libft/ fclean
	
re: fclean all

.PHONY: all clean fclean re

include $(wildcard $(dependency_files))
