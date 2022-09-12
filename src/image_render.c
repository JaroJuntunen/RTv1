/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:13:13 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/12 16:03:12 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	creat_primary_ray(t_ray *ray, int x, int y, t_rtv *rtv)
{
	ray->dir = add_vectors(rtv->camera.l, multiply_vect_float(rtv->camera.u,
				((float)x * (rtv->camera.plane_w / WIN_W))));
	ray->dir = add_vectors(ray->dir, multiply_vect_float(rtv->camera.v,
				((float)y * (rtv->camera.plane_h / WIN_H))));
	ray->dir = minus_vectors(rtv->camera.pos, ray->dir);
	ray->dir = divide_vect_float(ray->dir,
			sqrt((dot_prdct(ray->dir, ray->dir))));
	rtv->orig_ray = ray;
}

double	get_shape_intersections(t_ray *ray, t_rtv *rtv, int count)
{
	double	ret;

	rtv->t[0] = -1.0;
	rtv->t[1] = -1.0;
	if (ft_strcmp(rtv->shape[count].type, "sphere") == 0)
		ret = sphere_intersection(ray, rtv, count);
	else if (ft_strcmp(rtv->shape[count].type, "cylinder") == 0)
		ret = cylinder_intersection(ray, rtv, count);
	else if (ft_strcmp(rtv->shape[count].type, "plane") == 0)
		ret = plane_intersection(ray, rtv, count);
	else if (ft_strcmp(rtv->shape[count].type, "cone") == 0)
		ret = cone_intersection(ray, rtv, count);
	else
		ret = -1.0;
	return (ret);
}

int	ray_shooter(t_ray *ray, t_rtv *rtv)
{
	double	ret;
	int		count;

	count = 0;
	rtv->clo_ret = -1.0;
	while (count < rtv->shape_count)
	{
		ret = get_shape_intersections(ray, rtv, count);
		if (ret >= 0.0)
		{
			if (rtv->clo_ret == -1 || ret < rtv->clo_ret)
			{
				rtv->clo_shape = count;
				rtv->clo_ret = ret;
				rtv->clo_t[0] = rtv->t[0];
				rtv->clo_t[1] = rtv->t[1];
			}
		}
		count++;
	}
	if (rtv->clo_ret == -1 || ((rtv->clo_ret > 0.0)
			&& (check_shadow(ray, rtv) == 1)))
		return (0x00000000);
	return (get_color(rtv, ray));
}

static void	creat_camera(t_rtv *rtv)
{
	rtv->camera.v_up = divide_vect_float(rtv->camera.v_up,
			sqrt(dot_prdct(rtv->camera.v_up, rtv->camera.v_up)));
	rtv->camera.n = minus_vectors(rtv->camera.pos, rtv->camera.coi);
	rtv->camera.n = divide_vect_float(rtv->camera.n,
			sqrt(dot_prdct(rtv->camera.n, rtv->camera.n)));
	rtv->camera.n.z *= -1.0;
	rtv->camera.u = cross_product(rtv->camera.n, rtv->camera.v_up);
	rtv->camera.u = divide_vect_float(rtv->camera.u,
			sqrt(dot_prdct(rtv->camera.u, rtv->camera.u)));
	rtv->camera.v = cross_product(rtv->camera.u, rtv->camera.n);
	rtv->camera.c = minus_vectors(rtv->camera.pos,
			multiply_vect_float(rtv->camera.n, 0.1));
	rtv->camera.plane_h = tan(1.04719 / 2) * 2 * 0.1;
	rtv->camera.plane_w = rtv->camera.plane_h * ((float)WIN_W / WIN_H);
	rtv->camera.l = minus_vectors(rtv->camera.c,
			multiply_vect_float(rtv->camera.u, (rtv->camera.plane_w / 2.0)));
	rtv->camera.l = minus_vectors(rtv->camera.l,
			multiply_vect_float(rtv->camera.v, rtv->camera.plane_h / 2.0));
}

void	render_image(t_rtv	*rtv)
{
	int		y;
	int		x;
	int		color;
	t_ray	ray;

	y = 0;
	creat_camera(rtv);
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray.start = rtv->camera.pos;
			creat_primary_ray(&ray, x, y, rtv);
			rtv->clo_t[0] = -1.0;
			rtv->clo_t[1] = -1.0;
			color = ray_shooter(&ray, rtv);
			rtv->frame_buffer.data[((y * WIN_W) + x)] = color;
			x++;
		}
		y++;
	}
}
