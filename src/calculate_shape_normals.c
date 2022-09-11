/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_shape_normals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:37:40 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/11 19:12:19 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	find_sphere_normal(t_rtv *rtv, t_ray *ray, int i)
{
	t_vector	normal;
	double		normal_len;

	normal = minus_vectors(ray->start, rtv->shape[i].pos);
	normal_len = sqrt((cros_prdct(normal, normal)));
	normal.x /= normal_len;
	normal.y /= normal_len;
	normal.z /= normal_len;
	return (normal);
}

t_vector	find_cylinder_normal(t_rtv *rtv, t_ray *ray, int i)
{
	t_vector	temp;
	t_vector	temp_axel;
	t_vector	normal;
	double		len;
	double		axel_len;

	temp = minus_vectors(ray->start, rtv->shape[i].pos);
	len = ((cros_prdct(temp, temp)));
	len = sqrt(len - (rtv->shape[i].r
				* rtv->shape[i].r));
	temp_axel = minus_vectors(rtv->shape[i].cyl_h,
			rtv->shape[i].pos);
	axel_len = sqrt((cros_prdct(temp_axel, temp_axel)));
	temp_axel = divide_vect_float(temp_axel, axel_len);
	if (cros_prdct(divide_vect_float(temp, len), temp_axel) < 0)
		len *= -1.0;
	temp_axel = multiply_vect_float(temp_axel, len);
	temp_axel = add_vectors(temp_axel, rtv->shape[i].pos);
	
	
	normal = minus_vectors(ray->start, temp_axel);
	normal = divide_vect_float(normal, sqrt((cros_prdct(normal, normal))));
	return (normal);
}

t_vector	find_plane_normals(t_rtv *rtv, int i)
{
	t_vector	normal;
	double		normal_len;

	normal = rtv->shape[i].cyl_h;
	normal_len = sqrt((cros_prdct(normal, normal)));
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
	axel_len = sqrt((cros_prdct(axel, axel)));
	axel = divide_vect_float(axel, axel_len);
	relative_r = (rtv->shape[i].r / axel_len);
	temp = minus_vectors(ray->start, rtv->shape[i].cyl_h);
	len = (sqrt(cros_prdct(temp, temp)));
	temp = divide_vect_float(temp, len);

	axel_len = sqrt((len * len) + ((len * relative_r) * (len * relative_r)));
	if (cros_prdct(axel, temp) < 0.0)
		axel_len *= -1.0;
	axel.x = rtv->shape[i].cyl_h.x + (axel.x * axel_len);
	axel.y = rtv->shape[i].cyl_h.y + (axel.y * axel_len);
	axel.z = rtv->shape[i].cyl_h.z + (axel.z * axel_len);
	temp = minus_vectors(ray->start, axel);
	temp = divide_vect_float(temp, sqrt((cros_prdct(temp, temp))));
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
