/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:19:11 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/23 19:56:54 by jjuntune         ###   ########.fr       */
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

int		check_shadow(t_ray *ray, t_rtv *rtv)
{
	double	ret;
	int		count;
	t_ray	ofset_ray;

	count = 0;
	ret = -1;
	ray->start.x = (ray->dir.x * rtv->clo_ret);
	ray->start.y = (ray->dir.y * rtv->clo_ret);
	ray->start.z = (ray->dir.z * rtv->clo_ret);
	ray->dir = minus_vectors(rtv->light.pos, ray->start);
	rtv->light.dist = sqrt((m_a_vector(ray->dir, ray->dir)));
	ray->dir.x /= rtv->light.dist;
	ray->dir.y /= rtv->light.dist;
	ray->dir.z /= rtv->light.dist;
	ofset_ray.dir = ray->dir;
	ofset_ray.start = ray->start;
	if (ft_strcmp(rtv->shape[rtv->clo_shape].type, "plane") == 0)
		ofset_plane_dir(&ofset_ray, rtv);
	else
		ofset_dir(&ofset_ray);
	while (ret < 0.000000 && count < rtv->shape_count)
	{
		if (ft_strcmp(rtv->shape[count].type, "sphere") == 0)
			ret = sphere_intersection(&ofset_ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "cylinder") == 0)
			ret = cylinder_intersection(&ofset_ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "plane") == 0)
			ret = plane_intersection(&ofset_ray, rtv, count);
		else if (ft_strcmp(rtv->shape[count].type, "cone") == 0)
			ret = cone_intersection(&ofset_ray, rtv, count);
		count++;
		if (ret > rtv->light.dist)
			ret = -1;
	}
	if (ret < 0.00000)
		return (0);
	return (1);
}
