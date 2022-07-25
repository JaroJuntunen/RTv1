/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:19:11 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/20 10:44:01 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		check_shadow(t_ray *ray, t_rtv *rtv)
{
	float len;
	int		i;

	rtv->clo_shape = 0;
	ray->start.x = (ray->dir.x / rtv->clo_ret);
	ray->start.y = (ray->dir.y / rtv->clo_ret);
	ray->start.z = (ray->dir.z / rtv->clo_ret);
	//printf("%f, %f, %f\n",ray->start.x, ray->start.y, ray->start.z);
	ray->dir = minus_vectors(rtv->light.pos, ray->start);
	len = sqrt((m_a_vector(ray->dir, ray->dir)));
	//printf("%f, %f, %f\n",ray->dir.x, ray->dir.y, ray->dir.z);
	ray->dir.x /= len;
	ray->dir.y /= len;
	ray->dir.z /= len;
	//printf("%f, %f, %f\n",ray->dir.x, ray->dir.y, ray->dir.z);
	if (rtv->shape[rtv->clo_shape].type == 's')
	{
		i = shadow_sphere_intersection(ray, rtv, rtv->clo_shape);
		if (i == 1)
			return (0);
	}
	else if (rtv->shape[rtv->clo_shape].type == 'c')
	{
		i = shadow_sphere_intersection(ray, rtv, rtv->clo_shape);
		if (i == 1)
			return (0);
	}
	else if (rtv->shape[rtv->clo_shape].type == 'p')
	{
		i = shadow_sphere_intersection(ray, rtv, rtv->clo_shape);
		if (i == 1)
			return (0);
	}
	return (1);
}
