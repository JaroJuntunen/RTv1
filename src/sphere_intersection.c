/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:28:21 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/07 16:40:47 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	sphere_intersection(t_ray *ray, t_rtv *rtv, int count)
{
	t_vector	w;
	double		discr;
	double		b;
	double		ret;

	w = minus_vectors(ray->start, rtv->shape[count].pos);
	b = (2 * m_a_vector(ray->dir, w));
	discr = (b * b);
	discr -= (4 * m_a_vector(ray->dir, ray->dir) * (m_a_vector(w, w)
				- (rtv->shape[count].r * rtv->shape[count].r)));
	if (discr >= 0)
	{
		discr = sqrt(discr);
		rtv->t[0] = (-b + discr) / (2 * m_a_vector(ray->dir, ray->dir));
		rtv->t[1] = (-b - discr) / (2 * m_a_vector(ray->dir, ray->dir));
		if (rtv->t[0] < rtv->t[1] && rtv->t[0] > (double)0)
			ret = rtv->t[0];
		else
			ret = rtv->t[1];
	}
	else
		ret = -1.0f;
	return (ret);
}
