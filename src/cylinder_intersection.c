/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:45:46 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/12 16:03:12 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	get_abc(t_ray *ray, t_rtv *rtv, t_shape_calc	*cylinder, int i)
{
	cylinder->abc.x = (dot_prdct(ray->dir, ray->dir)
			- (dot_prdct(ray->dir, cylinder->h)
				* dot_prdct(ray->dir, cylinder->h)));
	cylinder->abc.y = (2 * (dot_prdct(ray->dir, cylinder->w)
				- (dot_prdct(ray->dir, cylinder->h)
					* dot_prdct(cylinder->w, cylinder->h))));
	cylinder->abc.z = (dot_prdct(cylinder->w, cylinder->w)
			- (dot_prdct(cylinder->w, cylinder->h)
				* dot_prdct(cylinder->w, cylinder->h))
			- (rtv->shape[i].r * rtv->shape[i].r));
}

double	cylinder_intersection(t_ray *ray, t_rtv *rtv, int i)
{
	t_shape_calc	cylinder;

	cylinder.w = minus_vectors(ray->start, rtv->shape[i].pos);
	cylinder.h = minus_vectors(rtv->shape[i].cyl_h, rtv->shape[i].pos);
	cylinder.h = divide_vect_float(cylinder.h,
			sqrt((dot_prdct(cylinder.h, cylinder.h))));
	get_abc(ray, rtv, &cylinder, i);
	cylinder.discr = ((cylinder.abc.y * cylinder.abc.y)
			- (4 * cylinder.abc.x * cylinder.abc.z));
	if (cylinder.discr >= 0)
	{
		cylinder.discr = sqrt(cylinder.discr);
		rtv->t[0] = (-cylinder.abc.y - cylinder.discr) / (2 * cylinder.abc.x);
		rtv->t[1] = (-cylinder.abc.y + cylinder.discr) / (2 * cylinder.abc.x);
		if (rtv->t[0] < rtv->t[1] && rtv->t[0] >= (double)0)
			return (rtv->t[0]);
		else
			return (rtv->t[1]);
	}
	return (-1);
}
