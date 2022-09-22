/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_shading.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:19:26 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/22 18:55:46 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	color_shade(t_rtv *rtv, double temp, double dist)
{
	dist /= 20;
	if (dist < 1)
		dist = 1;
	rtv->shape[rtv->clo_shape].temp_color.rgba[0]
		= (((int)rtv->shape[rtv->clo_shape].color.rgba[0] * temp / dist));
	rtv->shape[rtv->clo_shape].temp_color.rgba[1]
		= (((int)rtv->shape[rtv->clo_shape].color.rgba[1] * temp / dist));
	rtv->shape[rtv->clo_shape].temp_color.rgba[2]
		= (((int)rtv->shape[rtv->clo_shape].color.rgba[2] * temp / dist));
	rtv->shape[rtv->clo_shape].temp_color.rgba[3]
		= (((int)rtv->shape[rtv->clo_shape].color.rgba[3] * temp / dist));
}

/*
** If there is intersection whit object, this funcktion will calculate
** shape surface normal and distanse to light and calculates the color
** shade/intensity.
*/

int	get_color(t_rtv *rtv, t_ray *ray)
{
	double		temp;
	double		dist;
	t_vector	to_light;

	find_normal(ray, rtv, rtv->clo_shape);
	to_light = minus_vectors(ray->start, rtv->light.pos);
	dist = sqrt((dot_prdct(to_light, to_light)));
	temp = dot_prdct(ray->dir, rtv->shape[rtv->clo_shape].normal);
	if (temp < 0)
		temp *= -1.0;
	color_shade(rtv, temp, dist);
	return (rtv->shape[rtv->clo_shape].temp_color.value);
}

/*
** This will check if the camera is inside the shape in question.
*/

int	is_iside_cone(t_ray *ray, t_rtv *rtv)
{
	t_vector	temp_t0;
	t_vector	temp_t1;

	rtv->shape[rtv->clo_shape].in_shape = 0;
	if (ft_strcmp(rtv->shape[rtv->clo_shape].type, "cone") == 0)
	{
		temp_t0 = add_vectors(ray->dir,
				multiply_vect_float(ray->dir, rtv->clo_t[0]));
		temp_t1 = add_vectors(ray->dir,
				multiply_vect_float(ray->dir, rtv->clo_t[1]));
		temp_t0 = minus_vectors(rtv->shape[rtv->clo_shape].cyl_h, temp_t0);
		temp_t1 = minus_vectors(rtv->shape[rtv->clo_shape].cyl_h, temp_t1);
		temp_t0 = divide_vect_float(temp_t0,
				sqrt((dot_prdct(temp_t0, temp_t0))));
		temp_t1 = divide_vect_float(temp_t1,
				sqrt((dot_prdct(temp_t1, temp_t1))));
		if ((dot_prdct(temp_t0, temp_t1) < 0)
			|| (rtv->clo_t[0] < 0.0 && rtv->clo_t[1] > 0.0))
			rtv->shape[rtv->clo_shape].in_shape = 1;
	}
	else if (rtv->clo_t[0] < 0.0 && rtv->clo_t[1] > 0.0)
		rtv->shape[rtv->clo_shape].in_shape = 1;
	return (0);
}
