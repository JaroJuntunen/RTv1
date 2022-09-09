/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:07 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/09 17:56:13 by jjuntune         ###   ########.fr       */
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
# define WIN_H 750
# define MAX_SHAPES 100

union	u_color
{
	unsigned int	value;
	unsigned char	rgba[4];
};

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_shape
{
	char			*type;
	t_vector		pos;
	t_vector		cyl_h;
	double			r;
	t_vector		normal;
	union u_color	color;
	union u_color	temp_color;
	t_vector		temp_norm;
}					t_shape;

typedef struct s_light
{
	t_vector	pos;
	int			brightness;
	double		dist;
}				t_light;

typedef struct s_frame_buffer
{
	int			*data;
	int			data_len;
}				t_frame_buffer;

typedef struct s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	v_up;
	t_vector	coi;
	t_vector	v;
	t_vector	u;
	t_vector	n;
	t_vector	c;
	t_vector	l;
	double		plane_h;
	double		plane_w;
}				t_camera;

typedef struct s_shape_calc
{
	t_vector	h;
	t_vector	w;
	t_vector	abc;
	double		discr;
}				t_shape_calc;

typedef struct s_rtv
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		event;
	SDL_Texture		*texture;
	t_frame_buffer	frame_buffer;
	t_camera		camera;
	t_light			light;
	t_shape			*shape;
	int				clo_shape;
	double			clo_ret;
	double			t[2];
	double			clo_t[2];
	int				shape_count;
	double			len;
	t_ray			*orig_ray;
}					t_rtv;

double		cros_prdct(t_vector a, t_vector b);
t_vector	divide_vectors(t_vector a, t_vector b);
t_vector	multiply_vectors(t_vector a, t_vector b);
t_vector	minus_vectors(t_vector a, t_vector b);
t_vector	add_vectors(t_vector a, t_vector b);
int			check_shadow(t_ray *ray, t_rtv *rtv);
t_vector	multiply_vect_float(t_vector a, double b);
t_vector	cross_product(t_vector a, t_vector b);
t_vector	divide_vect_float(t_vector a, double b);
void		find_normal(t_ray *ray, t_rtv *rtv, int i);

void		render_image(t_rtv	*rtv);

int			read_imput(char **argv, t_rtv *rtv);

int			check_sphere(char **line_arg);
int			check_plane(char **line_arg);
int			check_cylinder(char **line_arg);
int			check_cone(char **line_arg);
int			check_light(char **line_arg);
int			check_color(char *arg);
int			check_r(char *arg);
int			check_coordinates_and_directions(char *arg);
void		check_and_correct_plane_normals(t_rtv *rtv);
int			is_it_light(char **line_arg);
int			check_camera(char **line_arg);

int			parser_error_handler(int error);

void		fill_shape(t_rtv *rtv, char *line, int i);
void		fill_shape(t_rtv *rtv, char *line, int i);
void		fill_sphere(t_rtv *rtv, char **line_arg, int i);
void		fill_plane(t_rtv *rtv, char **line_arg, int i);
void		fill_cone(t_rtv *rtv, char **line_arg, int i);
void		fill_cylinder(t_rtv *rtv, char **line_arg, int i);
void		fill_camera_arguments(t_rtv *rtv, char **line_arg);

t_vector	get_pos(char *line_arg_pos);
double		get_shape_desimals(char *line_arg_r);
int			get_color(t_rtv *rtv, t_ray *ray);

double		sphere_intersection(t_ray *ray, t_rtv *rtv, int count);
double		cylinder_intersection(t_ray *ray, t_rtv *rtv, int count);
double		plane_intersection(t_ray *ray, t_rtv *rtv, int count);
double		cone_intersection(t_ray *ray, t_rtv *rtv, int count);
#endif