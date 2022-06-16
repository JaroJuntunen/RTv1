/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:07 by jjuntune          #+#    #+#             */
/*   Updated: 2022/06/16 19:23:06 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "../build/libsdl2/include/SDL2/SDL.h"

# define WIN_W 500
# define WIN_H 360
# define FOV 1000
# define MAX_SHAPES 10

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_shape
{
	char		type;
	t_vector	pos;
	float		r;
	int			color;
}				t_shape;

typedef struct	s_frame_buffer
{
	int			*data;
	int			data_len;
}				t_frame_buffer;

typedef struct		s_RTv
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		event;
	SDL_Texture 	*texture;
	t_frame_buffer	frame_buffer;
	t_vector		camera;
	t_shape			shape[MAX_SHAPES];
	int				shape_count;
}					t_RTv;






double		m_a_vector(t_vector *a, t_vector *b);
t_vector	*divide_vectors(t_vector *a, t_vector *b);
t_vector	*multiply_vectors(t_vector *a, t_vector *b);
t_vector	minus_vectors(t_vector *a, t_vector *b);
t_vector	*add_vectors(t_vector *a, t_vector *b);

void	Render_Image(t_RTv	*RTv);
double	*sphere_Intersection(t_vector *ray, t_RTv *RTv , int count);

#endif