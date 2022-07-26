/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:28:21 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/26 15:59:03 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"


double	sphere_intersection(t_ray *ray, t_rtv *rtv , int count)
{
	double		t[2];
	t_vector	w;
	double		discr;
	double		b;
	double		ret;

	w = minus_vectors(ray->start, rtv->shape[count].pos);
	b = (2 * m_a_vector(ray->dir, w));
	discr = ((b * b) - (4 * m_a_vector(ray->dir , ray->dir)
		* (m_a_vector(w , w) - (rtv->shape[count].r * rtv->shape[count].r))));
	if (discr >= 0)
	{
		discr = sqrt(discr);
		t[0] = (-b + discr) / (2 * m_a_vector(ray->dir ,ray->dir));
		t[1] = (-b - discr) / (2 * m_a_vector(ray->dir, ray->dir));
		if (t[0] < t[1] && t[0] > (double)0)
			ret = t[0];
		else
			ret = t[1];
	}
	else
		ret = -1.0f;
	return (ret);
}

int	shadow_sphere_intersection(t_ray *ray, t_rtv *rtv , int count)
{
	double		t[2];
	t_vector	w;
	double		discr;
	double		b;


	w = minus_vectors(ray->start, rtv->light.pos);
	b = (2 * m_a_vector(ray->dir, w));
	discr = ((b * b) - (4 * m_a_vector(ray->dir , ray->dir)
		* (m_a_vector(w , w) - (rtv->shape[count].r * rtv->shape[count].r))));
	if (discr >= 0)
	{
		discr = sqrt(discr);
		t[0] = (-b + discr) / (2 * m_a_vector(ray->dir, ray->dir));
		t[1] = (-b - discr) / (2 * m_a_vector(ray->dir, ray->dir));
		if (t[0] > t[1] && t[0] > (double)0 && t[1] > (double)0)
			return (1);
	}
	return (0);
}
