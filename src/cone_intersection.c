/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:29:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/11 19:54:38 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static double	calculate_a(t_ray *ray, double m, t_vector	h)
{
	double		temp1;
	double		temp2;
	double		temp3;

	temp1 = cros_prdct(ray->dir, ray->dir);
	temp2 = (m * (cros_prdct(ray->dir, h) * cros_prdct(ray->dir, h)));
	temp3 = (cros_prdct(ray->dir, h) * cros_prdct(ray->dir, h));
	return (temp1 - temp2 - temp3);
}

static double	calculate_b(t_ray *ray, double m, t_vector	w, t_vector	h)
{
	double		temp1;
	double		temp2;
	double		temp3;

	temp1 = cros_prdct(ray->dir, w);
	temp2 = m * cros_prdct(ray->dir, h) * cros_prdct(w, h);
	temp3 = cros_prdct(ray->dir, h) * cros_prdct(w, h);
	return (2 * (temp1 - temp2 - temp3));
}

static double	calculate_c(double m, t_vector	w, t_vector	h)
{
	double		temp1;
	double		temp2;
	double		temp3;

	temp1 = cros_prdct(w, w);
	temp2 = m * cros_prdct(w, h) * cros_prdct(w, h);
	temp3 = cros_prdct(w, h) * cros_prdct(w, h);
	return (temp1 - temp2 - temp3);
}

double	cone_intersection(t_ray *ray, t_rtv *rtv, int count)
{
	double		m;
	double		ret;
	t_vector	w;
	t_vector	h;
	t_vector	abc;

	w = minus_vectors(ray->start, rtv->shape[count].cyl_h);
	h = minus_vectors(rtv->shape[count].pos, rtv->shape[count].cyl_h);
	m = ((rtv->shape[count].r * rtv->shape[count].r) / ((cros_prdct(h, h))));
	h = divide_vect_float(h, sqrt((cros_prdct(h, h))));
	abc.x = calculate_a(ray, m, h);
	abc.y = calculate_b(ray, m, w, h);
	abc.z = calculate_c(m, w, h);
	if ((abc.y * abc.y) - (4 * abc.x * abc.z) > 0)
	{
		rtv->t[0] = (-abc.y - sqrt((abc.y * abc.y)
					- (4 * abc.x * abc.z))) / (2 * abc.x);
		rtv->t[1] = (-abc.y + sqrt((abc.y * abc.y)
					- (4 * abc.x * abc.z))) / (2 * abc.x);
		if (rtv->t[0] < rtv->t[1] && rtv->t[0] > (double)0)
			ret = rtv->t[0];
		else
			ret = rtv->t[1];
		return (ret);
	}
	return (-1);

}
