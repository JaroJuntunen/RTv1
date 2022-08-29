/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_shading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:19:26 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/23 20:44:55 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	color_shade(t_rtv *rtv, double temp)
{
	rtv->shape[rtv->clo_shape].temp_color.rgba[0] = (((int)rtv->shape[rtv->clo_shape].color.rgba[0] * temp));
	rtv->shape[rtv->clo_shape].temp_color.rgba[1] = (((int)rtv->shape[rtv->clo_shape].color.rgba[1] * temp));
	rtv->shape[rtv->clo_shape].temp_color.rgba[2] = (((int)rtv->shape[rtv->clo_shape].color.rgba[2] * temp));
	rtv->shape[rtv->clo_shape].temp_color.rgba[3] = (((int)rtv->shape[rtv->clo_shape].color.rgba[3] * temp));
}


int		get_color(t_rtv *rtv, t_ray *ray)
{
	double		temp;

	if (rtv->clo_ret > 0)
	{
		find_normal(ray, rtv);
		temp = m_a_vector(ray->dir, rtv->shape[rtv->clo_shape].normal);
		if (temp < 0)
			return (0x00000000);
		color_shade(rtv, temp);
		return (rtv->shape[rtv->clo_shape].temp_color.value);
	}
	return (0x00000000);
}
