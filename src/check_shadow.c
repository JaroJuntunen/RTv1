/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:19:11 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/06 13:19:32 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ofset_dir(t_ray *ray)
{
	if (ray->dir.x >= 0)
		ray->start.x -= 0.000001;
	else
		ray->start.x += 0.000001;
	if (ray->dir.y >= 0)
		ray->start.y -= 0.000001;
	else
		ray->start.y += 0.000001;
	if (ray->dir.z >= 0)
		ray->start.z -= 0.000001;
	else
		ray->start.z += 0.000001;
}

void	ofset_plane_dir(t_ray *ray, t_rtv *rtv)
{
	if (rtv->shape[rtv->clo_shape].cyl_h.x > 0)
		ray->start.x -= 0.0001;
	else
		ray->start.x += 0.0001;
	if (rtv->shape[rtv->clo_shape].cyl_h.y > 0)
		ray->start.y -= 0.0001;
	else
		ray->start.y += 0.0001;
	if (rtv->shape[rtv->clo_shape].cyl_h.z > 0)
		ray->start.z -= 0.0001;
	else
		ray->start.z += 0.0001;
}

void	offset_and_declare_shadow_ray(t_rtv *rtv, t_ray *ray)
{
	ray->start = add_vectors(ray->start,
			multiply_vect_float(ray->dir, rtv->clo_ret));
	ray->dir = minus_vectors(rtv->light.pos, ray->start);
	ray->dir = divide_vect_float(ray->dir,
			sqrt((m_a_vector(ray->dir, ray->dir))));
	ofset_dir(ray);
}

int	check_shadow(t_ray *ray, t_rtv *rtv)
{
	double	ret;
	int		count;

	count = 0;
	ret = -1;
	offset_and_declare_shadow_ray(rtv, ray);
	while (ret < 0.000000 && count < rtv->shape_count)
	{
		if (ft_strcmp(rtv->shape[count].type, "sphere") == 0)
			ret = sphere_intersection(ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "cylinder") == 0)
			ret = cylinder_intersection(ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "plane") == 0)
			ret = plane_intersection(ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "cone") == 0)
			ret = cone_intersection(ray, rtv, count);
		count++;
		if (ret > rtv->light.dist)
			ret = -1;
	}
	if (ret < 0.00000)
		return (0);
	return (1);
}
