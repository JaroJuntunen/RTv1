/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:19:11 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/22 17:53:28 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** All the ofset functions are ofsetting the starting point of the shadow
** ray. Thay need to be ofsetted to get clear shadows and colors.
*/

void	ofset_dir(t_ray *ray, t_rtv *rtv)
{
	double	ofset_dist;

	ofset_dist = 0.0001;
	ray->start.x += rtv->shape[rtv->clo_shape].normal.x * ofset_dist;
	ray->start.y += rtv->shape[rtv->clo_shape].normal.y * ofset_dist;
	ray->start.z += rtv->shape[rtv->clo_shape].normal.z * ofset_dist;
}

void	ofset_plane_dir(t_ray *ray, t_rtv *rtv)
{
	double	ofset_dist;

	ofset_dist = 0.0001;
	ray->start.x -= rtv->shape[rtv->clo_shape].cyl_h.x * ofset_dist;
	ray->start.y -= rtv->shape[rtv->clo_shape].cyl_h.y * ofset_dist;
	ray->start.z -= rtv->shape[rtv->clo_shape].cyl_h.z * ofset_dist;
}

void	ofset_dir_inside(t_ray *ray)
{
	double	ofset_dist;

	ofset_dist = 0.0001;
	if (ray->dir.x > 0)
		ray->start.x += ofset_dist;
	else if (ray->dir.x < 0)
		ray->start.x -= ofset_dist;
	if (ray->dir.y > 0)
		ray->start.y += ofset_dist;
	else if (ray->dir.y < 0)
		ray->start.y -= ofset_dist;
	if (ray->dir.z > 0)
		ray->start.z += ofset_dist;
	else if (ray->dir.z < 0)
		ray->start.z -= ofset_dist;
}

/*
** declear swhadow ray so we can check if the shape is in the shadow
*/

void	offset_and_declare_shadow_ray(t_rtv *rtv, t_ray *ray)
{
	is_iside_cone(ray, rtv);
	ray->start = add_vectors(ray->start,
			multiply_vect_float(ray->dir, rtv->clo_ret));
	ray->dir = minus_vectors(rtv->light.pos, ray->start);
	ray->dir = minus_vectors(rtv->light.pos, ray->start);
	rtv->light.dist = sqrt((dot_prdct(ray->dir, ray->dir)));
	ray->dir = divide_vect_float(ray->dir, rtv->light.dist);
	find_normal(ray, rtv, rtv->clo_shape);
	if (ft_strcmp(rtv->shape[rtv->clo_shape].type, "plane") == 0)
		ofset_plane_dir(ray, rtv);
	else if (rtv->shape[rtv->clo_shape].in_shape == 1)
		ofset_dir_inside(ray);
	else
		ofset_dir(ray, rtv);
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
		if (ret > rtv->light.dist || ret < 0)
			ret = -1.0;
	}
	if (ret < 0.00000)
		return (0);
	return (1);
}
