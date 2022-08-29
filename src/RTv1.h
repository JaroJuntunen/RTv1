/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:07 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/29 19:00:55 by jjuntune         ###   ########.fr       */
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
	char		*type;
	t_vector	pos;
	t_vector	cyl_h;
	double		r;
	t_vector	normal;
	union u_color	color;
	union u_color	temp_color;
	t_vector		temp_norm;
}				t_shape;

typedef struct s_light
{
	t_vector	pos;
	int			brightness;
	double		dist;
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
	t_vector	coi;
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
	t_shape			*shape;
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
t_vector	multiply_vect_float(t_vector a, double b);
t_vector	cross_product(t_vector a, t_vector b);
t_vector	divide_vect_float(t_vector a, double b);
void	find_normal(t_ray *ray, t_rtv *rtv);

void		render_image(t_rtv	*rtv);

int		read_imput(char **argv, t_rtv *rtv);
void	fill_shape(t_rtv *rtv,char *line, int i);

int		check_sphere(char **line_arg);
int		check_plane(char **line_arg);
int		check_cylinder(char **line_arg);
int		check_cone(char **line_arg);
int		check_light(char **line_arg);
int		check_color(char *arg);
int		check_r(char *arg);
int		check_coordinates_and_directions(char *arg);
void	check_and_correct_plane_normals(t_rtv *rtv);
int		parser_error_handler(int error);

void	fill_shape(t_rtv *rtv,char *line, int i);
void	fill_sphere(t_rtv *rtv, char **line_arg, int i);
void	fill_plane(t_rtv *rtv, char **line_arg, int i);
void	fill_cone(t_rtv *rtv, char **line_arg, int i);
void	fill_cylinder(t_rtv *rtv, char **line_arg, int i);

t_vector	get_pos(char *line_arg_pos);
double	get_shape_desimals(char *line_arg_r);

double		sphere_intersection(t_ray *ray, t_rtv *rtv , int count);
double		sphere_intersection_shadow(t_ray *ray, t_rtv *rtv , int count);

double		cylinder_intersection(t_ray *ray, t_rtv *rtv , int count);
double		cylinder_intersection_shadow(t_ray *ray, t_rtv *rtv , int count);

double		plane_intersection(t_ray *ray, t_rtv *rtv , int count);

double		cone_intersection(t_ray *ray, t_rtv *rtv , int count);
double		cone_intersection_shadow(t_ray *ray, t_rtv *rtv , int count);

int		get_color(t_rtv *rtv, t_ray *ray);
#endif