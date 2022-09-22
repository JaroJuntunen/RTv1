/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_shape_normals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:34:34 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/22 19:22:37 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	find_sphere_normal(t_rtv *rtv, t_ray *ray, int i)
{
	t_vector	normal;
	double		normal_len;

	normal = minus_vectors(ray->start, rtv->shape[i].pos);
	normal_len = sqrt((dot_prdct(normal, normal)));
	normal.x /= normal_len;
	normal.y /= normal_len;
	normal.z /= normal_len;
	return (normal);
}

t_vector	find_cylinder_normal(t_rtv *rtv, t_ray *ray, int i)
{
	t_vector	result;
	t_vector	hypotenuse;
	t_vector	hit_along_cyldir;
	t_vector	temp;

	hypotenuse = minus_vectors(ray->start, rtv->shape[rtv->clo_shape].pos);
	temp = minus_vectors(rtv->shape[i].cyl_h, rtv->shape[i].pos);
	temp = divide_vect_float(temp, sqrt(dot_prdct(temp, temp)));
	hit_along_cyldir = add_vectors(rtv->shape[rtv->clo_shape].pos,
			multiply_vect_float(temp, dot_prdct(hypotenuse, temp)));
	result = minus_vectors(ray->start, hit_along_cyldir);
	result = divide_vect_float(result, sqrt(dot_prdct(result, result)));
	return (result);
}

t_vector	find_plane_normals(t_rtv *rtv, int i)
{
	t_vector	normal;
	double		normal_len;

	normal = rtv->shape[i].cyl_h;
	normal_len = sqrt((dot_prdct(normal, normal)));
	normal.x /= normal_len;
	normal.y /= normal_len;
	normal.z /= normal_len;
	return (normal);
}

t_vector	find_cone_normals(t_rtv *rtv, t_ray *ray, int i)
{
	t_vector	axel;
	t_vector	temp;
	double		len;
	double		axel_len;
	double		relative_r;

	axel = minus_vectors(rtv->shape[i].cyl_h,
			rtv->shape[i].pos);
	axel_len = sqrt((dot_prdct(axel, axel)));
	axel = divide_vect_float(axel, axel_len);
	relative_r = (rtv->shape[i].r / axel_len);
	temp = minus_vectors(ray->start, rtv->shape[i].cyl_h);
	len = (sqrt(dot_prdct(temp, temp)));
	temp = divide_vect_float(temp, len);
	axel_len = sqrt((len * len) + ((len * relative_r) * (len * relative_r)));
	if (dot_prdct(axel, temp) < 0.0)
		axel_len *= -1.0;
	axel.x = rtv->shape[i].cyl_h.x + (axel.x * axel_len);
	axel.y = rtv->shape[i].cyl_h.y + (axel.y * axel_len);
	axel.z = rtv->shape[i].cyl_h.z + (axel.z * axel_len);
	temp = minus_vectors(ray->start, axel);
	temp = divide_vect_float(temp, sqrt((dot_prdct(temp, temp))));
	return (temp);
}

void	find_normal(t_ray *ray, t_rtv *rtv, int i)
{
	if (ft_strcmp(rtv->shape[i].type, "sphere") == 0)
		rtv->shape[i].normal = find_sphere_normal(rtv, ray, i);
	if (ft_strcmp(rtv->shape[i].type, "cylinder") == 0)
		rtv->shape[i].normal = find_cylinder_normal(rtv, ray, i);
	else if (ft_strcmp(rtv->shape[i].type, "plane") == 0)
	rtv->shape[i].normal = find_plane_normals(rtv, i);
	else if (ft_strcmp(rtv->shape[i].type, "cone") == 0)
		rtv->shape[i].normal = find_cone_normals(rtv, ray, i);
}
