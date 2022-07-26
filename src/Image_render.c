/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:52:35 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/26 16:04:30 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		get_color(double ret, t_rtv *rtv, int count)
{
	int		color;

	color = rtv->shape[count].color;
	if (ret > (double)0)
		return(color);
	return(0x000000);
	
}
float	lerp1d(float a, float b, float t)
{
	return ((1 - t) * a + t * b);
}

void	creat_primary_ray(t_ray *ray, int x, int y, t_rtv *rtv)
{
	ray->dir.x = lerp1d(-1.0, 1.0, (1.0f / WIN_W) * (x + 0.5));
	ray->dir.y = lerp1d(-0.75, 0.75, (1.0f / WIN_H) * (y + 0.5));
	ray->dir.z = 100;
	rtv->len = sqrt((m_a_vector(ray->dir, ray->dir)));
	ray->dir.x /= rtv->len;
	ray->dir.y /= rtv->len;
	ray->dir.z /= rtv->len;
}

int	ray_shooter(t_ray *ray,t_rtv *rtv)
{
	double	ret;
	int		count;

	count = 0;
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
		if (count == 0)
		{
			rtv->clo_shape = count;
			rtv->clo_ret = ret;
		}
		else if (ret > 0)
		{
			if (rtv->clo_ret == -1 || ret < rtv->clo_ret)
			{
				rtv->clo_shape = count;
				rtv->clo_ret = ret;
			}
		}
		count++;
	}
	//if (check_shadow(ray,rtv) == 1)
	//	return (0x00000000);
	return (get_color(rtv->clo_ret, rtv, rtv->clo_shape));
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