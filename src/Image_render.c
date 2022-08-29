/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:52:35 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/29 21:08:28 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

float	lerp1d(float a, float b, float t)
{
	return ((1 - t) * a + t * b);
}

//void	creat_primary_ray(t_ray *ray, int x, int y, t_rtv *rtv)
//{
//	ray->dir.x = lerp1d(-1.0, 1.0, (1.0f / WIN_W) * x);
//	ray->dir.y = lerp1d(-0.75, 0.75, (1.0f / WIN_H) * y);
//	ray->dir.z = 2;
//	rtv->len = sqrt((m_a_vector(ray->dir, ray->dir)));
//	ray->dir.x /= rtv->len;
//	ray->dir.y /= rtv->len;
//	ray->dir.z /= rtv->len;
//}

void	creat_primary_ray(t_ray *ray, int x, int y, t_rtv *rtv)
{
	t_vector	v_up;
	t_vector	v;
	t_vector	u;
	t_vector	n;
	t_vector	c;
	t_vector	l;
	double plane_h;
	double plane_w;
	
	v_up.x = 0.0;
	v_up.y = 1.0;
	v_up.z = 0.0;
	v_up = divide_vect_float(v_up, sqrt(m_a_vector(v_up, v_up)));
	ray->coi.x = 0.0;
	ray->coi.y = 0.0;
	ray->coi.z = 1.0;
	n = minus_vectors(rtv->camera,ray->coi);
	n = divide_vect_float(n, sqrt(m_a_vector(n, n)));
	n.z *= -1.0;
	u = cross_product(n, v_up);
	u = divide_vect_float(u, sqrt(m_a_vector(u, u)));
	v = cross_product(u, n);
	c = minus_vectors(rtv->camera, multiply_vect_float(n, 0.1));
	plane_h = tan(1.04719 / 2) * 2 * 0.1;
	plane_w = plane_h * ((float)WIN_W / WIN_H);
	l = minus_vectors(c, multiply_vect_float(u, (plane_w / 2.0)));
	l = minus_vectors(l, multiply_vect_float(v, plane_h / 2.0));
	ray->dir = add_vectors(l, multiply_vect_float(u, ((float)x * (plane_w / WIN_W))));
	ray->dir = add_vectors(ray->dir, multiply_vect_float(v, ((float)y * (plane_h / WIN_H))));
	ray->dir = minus_vectors(rtv->camera, ray->dir);
	ray->dir = divide_vect_float(ray->dir, sqrt((m_a_vector(ray->dir, ray->dir))));
	//printf("%f %f %f\n", ray->dir.x, ray->dir.y, ray->dir.z);
}


int	ray_shooter(t_ray *ray,t_rtv *rtv)
{
	double	ret;
	int		count;

	count = 0;
	rtv->clo_ret = -1.0;
	while (count < rtv->shape_count)
	{
		
		if (ft_strcmp(rtv->shape[count].type, "sphere") == 0)
			ret = sphere_intersection(ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "cylinder") == 0)
			ret = cylinder_intersection(ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "plane") == 0)
			ret = plane_intersection(ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "cone") == 0)
			ret = cone_intersection(ray, rtv, count);
		if (ret >= 0.0)
		{
			if (rtv->clo_ret == -1 || ret < rtv->clo_ret)
			{
				rtv->clo_shape = count;
				rtv->clo_ret = ret;
			}
		}
		count++;
	}
	if (rtv->clo_ret == -1 || ((rtv->clo_ret > 0.0) && (check_shadow(ray,rtv) == 1)))
		return (0x00000000);
	//return(rtv->shape[rtv->clo_shape].color.value);
	return (get_color(rtv, ray));
}

void	render_image(t_rtv	*rtv)
{
	int	y;
	int	x;
	int	color;
	t_ray ray;
	
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			
			ray.start = rtv->camera;
			
			creat_primary_ray(&ray, x, y, rtv);
			color = ray_shooter(&ray, rtv);
			
			rtv->frame_buffer.data[ ((y * WIN_W) + x)] = color;
			x++;
		}
		y++;
	}
}