/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_shape_normals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:37:40 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/07 17:03:49 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	find_sphere_normal(t_rtv *rtv, t_ray *ray)
{
	t_vector	normal;
	double		normal_len;

	normal = minus_vectors(ray->start, rtv->shape[rtv->clo_shape].pos);
	normal_len = sqrt((m_a_vector(normal, normal)));
	normal.x /= normal_len;
	normal.y /= normal_len;
	normal.z /= normal_len;
	return (normal);
}

t_vector	find_cylinder_normal(t_rtv *rtv, t_ray *ray)
{
	t_vector	temp;
	t_vector	temp_axel;
	t_vector	normal;
	double		len;
	double		axel_len;

	temp = minus_vectors(ray->start, rtv->shape[rtv->clo_shape].pos);
	len = ((m_a_vector(temp, temp)));
	len = sqrt(len - (rtv->shape[rtv->clo_shape].r
				* rtv->shape[rtv->clo_shape].r));
	temp_axel = minus_vectors(rtv->shape[rtv->clo_shape].cyl_h,
			rtv->shape[rtv->clo_shape].pos);
	if (m_a_vector(temp, temp_axel) < 0)
		len *= -1.0;
	axel_len = sqrt((m_a_vector(temp_axel, temp_axel)));
	temp_axel = divide_vect_float(temp_axel, axel_len);
	temp_axel = multiply_vect_float(temp_axel, len);
	temp_axel = add_vectors(temp_axel, rtv->shape[rtv->clo_shape].pos);
	normal = minus_vectors(ray->start, temp_axel);
	normal = divide_vect_float(normal, sqrt((m_a_vector(normal, normal))));
	return (normal);
}

t_vector	find_plane_normals(t_rtv *rtv)
{
	t_vector	normal;
	double		normal_len;

	normal = rtv->shape[rtv->clo_shape].cyl_h;
	normal_len = sqrt((m_a_vector(normal, normal)));
	normal.x /= normal_len;
	normal.y /= normal_len;
	normal.z /= normal_len;
	return (normal);
}

t_vector	find_cone_normals(t_rtv *rtv, t_ray *ray)
{
	t_vector	axel;
	t_vector	temp;
	double		len;
	double		axel_len;
	double		relative_r;

	axel = minus_vectors(rtv->shape[rtv->clo_shape].cyl_h,
			rtv->shape[rtv->clo_shape].pos);
	axel_len = sqrt((m_a_vector(axel, axel)));
	relative_r = (rtv->shape[rtv->clo_shape].r / axel_len);
	temp = minus_vectors(ray->start, rtv->shape[rtv->clo_shape].pos);
	len = (sqrt(m_a_vector(temp, temp)));
	len = sqrt((len * len) + ((len * relative_r) * (len * relative_r)));
	axel.x = rtv->shape[rtv->clo_shape].pos.x + ((axel.x / axel_len) * len);
	axel.y = rtv->shape[rtv->clo_shape].pos.y + ((axel.y / axel_len) * len);
	axel.z = rtv->shape[rtv->clo_shape].pos.z + ((axel.z / axel_len) * len);
	temp = minus_vectors(ray->start, axel);
	temp = divide_vect_float(temp, sqrt((m_a_vector(temp, temp))));
	return (temp);
}

void	find_normal(t_ray *ray, t_rtv *rtv)
{
	if (ft_strcmp(rtv->shape[rtv->clo_shape].type, "sphere") == 0)
		rtv->shape[rtv->clo_shape].normal = find_sphere_normal(rtv, ray);
	if (ft_strcmp(rtv->shape[rtv->clo_shape].type, "cylinder") == 0)
		rtv->shape[rtv->clo_shape].normal = find_cylinder_normal(rtv, ray);
	else if (ft_strcmp(rtv->shape[rtv->clo_shape].type, "plane") == 0)
	rtv->shape[rtv->clo_shape].normal = find_plane_normals(rtv);
	else if (ft_strcmp(rtv->shape[rtv->clo_shape].type, "cone") == 0)
		rtv->shape[rtv->clo_shape].normal = find_cone_normals(rtv, ray);
}
