/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:07 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/26 15:41:52 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../build/libsdl2/include/SDL2/SDL.h"

# define WIN_W 1000
# define WIN_H 700
# define MAX_SHAPES 100

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_shape
{
	char		*type;
	t_vector	pos;
	t_vector	cyl_h;
	double		r;
	int			color;
}				t_shape;

typedef struct s_light
{
	t_vector	pos;
	int			brightness;
}				t_light;

typedef struct	s_frame_buffer
{
	int			*data;
	int			data_len;
}				t_frame_buffer;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct		s_rtv
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		event;
	SDL_Texture 	*texture;
	t_frame_buffer	frame_buffer;
	t_vector		camera;
	t_light			light;
	t_shape			shape[MAX_SHAPES];
	int				clo_shape;
	double			clo_ret;
	int				shape_count;
	double			len;
}					t_rtv;






double		m_a_vector(t_vector a, t_vector b);
t_vector	divide_vectors(t_vector a, t_vector b);
t_vector	multiply_vectors(t_vector a, t_vector b);
t_vector	minus_vectors(t_vector a, t_vector b);
t_vector	add_vectors(t_vector a, t_vector b);
int			check_shadow(t_ray *ray, t_rtv *rtv);

void		render_image(t_rtv	*rtv);

double		sphere_intersection(t_ray *ray, t_rtv *rtv , int count);
double		cylinder_intersection(t_ray *ray, t_rtv *rtv , int count);
double		plane_intersection(t_ray *ray, t_rtv *rtv , int count);
double		cone_intersection(t_ray *ray, t_rtv *rtv , int count);

int			shadow_sphere_intersection(t_ray *ray, t_rtv *rtv , int count);
#endif