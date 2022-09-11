/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_shading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:19:26 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/11 18:13:58 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	color_shade(t_rtv *rtv, double temp, double dist)
{
	dist /= 10;
	if (dist < 1)
		dist = 1;
	if (temp > 1.0)
		temp = 1.0;
	rtv->shape[rtv->clo_shape].temp_color.value = rtv->shape[rtv->clo_shape].color.value;
	rtv->shape[rtv->clo_shape].temp_color.rgba[0]
		= (((int)rtv->shape[rtv->clo_shape].color.rgba[0] * (temp) / dist));
	rtv->shape[rtv->clo_shape].temp_color.rgba[1]
		= (((int)rtv->shape[rtv->clo_shape].color.rgba[1] * (temp) / dist));
	rtv->shape[rtv->clo_shape].temp_color.rgba[3]
		= (((int)rtv->shape[rtv->clo_shape].color.rgba[3] * (temp) / dist));
	rtv->shape[rtv->clo_shape].temp_color.rgba[2]
		= (((int)rtv->shape[rtv->clo_shape].color.rgba[2] * (temp) / dist));
}

int	get_color(t_rtv *rtv, t_ray *ray)
{
	double		temp;
	double		dist;
	t_vector	to_light;

	if (rtv->clo_ret > 0)
	{
		find_normal(ray, rtv, rtv->clo_shape);
		to_light = minus_vectors(ray->start, rtv->light.pos);
		dist = sqrt((cros_prdct(to_light, to_light)));
		temp = cros_prdct(ray->dir, rtv->shape[rtv->clo_shape].normal);
		if ((rtv->clo_t[0] < 0.0 && rtv->clo_t[1] > 0.0))
			temp *= -1.0;
		if (temp < 0)
			return (0x00000000);
		color_shade(rtv, temp, dist);
		return (rtv->shape[rtv->clo_shape].temp_color.value);
	}
	return (0x00000000);
}
