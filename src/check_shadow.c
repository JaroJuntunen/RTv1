/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:19:11 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/22 21:06:25 by jjuntune         ###   ########.fr       */
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

	ofset_dist = 0.00001;
	ray->start.x += rtv->shape[rtv->clo_shape].normal.x * ofset_dist;
	ray->start.y += rtv->shape[rtv->clo_shape].normal.y * ofset_dist;
	ray->start.z += rtv->shape[rtv->clo_shape].normal.z * ofset_dist;
}

void	ofset_plane_dir(t_ray *ray, t_rtv *rtv)
{
	double	ofset_dist;

	ofset_dist = 0.01;
	ray->start.x -= rtv->shape[rtv->clo_shape].cyl_h.x * ofset_dist;
	ray->start.y -= rtv->shape[rtv->clo_shape].cyl_h.y * ofset_dist;
	ray->start.z -= rtv->shape[rtv->clo_shape].cyl_h.z * ofset_dist;
}

/*
** declear swhadow ray so we can check if the shape is in the shadow
*/

void	offset_and_declare_shadow_ray(t_rtv *rtv, t_ray *ray)
{
	t_ray	orig;

	orig.dir = ray->dir;
	is_inside(ray, rtv);
	ray->start = add_vectors(ray->start,
			multiply_vect_float(ray->dir, rtv->clo_ret));
	ray->dir = minus_vectors(rtv->light.pos, ray->start);
	ray->dir = minus_vectors(rtv->light.pos, ray->start);
	rtv->light.dist = sqrt((dot_prdct(ray->dir, ray->dir)));
	ray->dir = divide_vect_float(ray->dir, rtv->light.dist);
	find_normal(ray, rtv, rtv->clo_shape);
	if (dot_prdct(orig.dir, rtv->shape[rtv->clo_shape].normal) > 0)
		rtv->shape[rtv->clo_shape].normal
			= multiply_vect_float(rtv->shape[rtv->clo_shape].normal, -1.0);
	if (ft_strcmp(rtv->shape[rtv->clo_shape].type, "plane") == 0)
		ofset_plane_dir(ray, rtv);
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
