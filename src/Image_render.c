/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:52:35 by jjuntune          #+#    #+#             */
/*   Updated: 2022/06/16 19:23:49 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h>

int		get_color(t_RTv *RTv,double *ret, int count)
{
	if (ret >= 0)
		return(RTv->shape[count].color);
	return(RTv->shape[count].color);
}
void	creat_primery_ray(t_vector *ray, t_RTv	*RTv, int x, int y)
{
	float	len;
	
	ray->x = RTv->camera.x - (x - (WIN_W / 2));
	ray->y = RTv->camera.y - (y - (WIN_H / 2));
	ray->z = RTv->camera.z - FOV;
	len = sqrt((m_a_vector(ray, ray)));
	ray->x = ray->x / len; 
	ray->y = ray->y / len;
	ray->z = ray->z / len;
}

int	ray_shooter(t_vector *ray,t_RTv *RTv)
{
	double	*ret;
	int		count;

	ret = 0;
	count = 0;
	while (count < RTv->shape_count && ret == 0)
	{
		if (RTv->shape[count].type == 's')
			ret = sphere_Intersection(ray, RTv, count);
	//	if (RTv->shape[count]->type == )
		//
	//	if (RTv->shape[count]->type == )
	//
	//	if (RTv->shape[count]->type == )
		count++;
	}
	return  (get_color(RTv, ret, count));
}

void	Render_Image(t_RTv	*RTv)
{
	int	y;
	int	x;
	int	color;
	int	pixel;
	t_vector ray;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			creat_primery_ray(&ray, RTv, x, y);
			color = ray_shooter(&ray, RTv);
			pixel = (y * WIN_W + x);
			RTv->frame_buffer.data[pixel] = color;
			x++;
		}
		y++;
	}
}