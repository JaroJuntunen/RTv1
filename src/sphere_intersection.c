/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:28:21 by jjuntune          #+#    #+#             */
/*   Updated: 2022/06/16 19:31:29 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	*t_calculate(double	*t, t_vector *abc)
{
	double	temp_a;
	double	temp_b;
	double	temp_c;

	temp_a = (abc->y * -1);
	temp_b = ((abc->y * abc->y) - (4 * (abc->x + abc->z)));
	temp_c = 2 * abc->x;
	if (temp_b >= 0)
	{
		t[0] = ((temp_a - sqrt(temp_b)) / temp_c);
		t[1] = ((temp_a + sqrt(temp_b)) / temp_c);
	}
	return (t);
}

double	*sphere_Intersection(t_vector *ray, t_RTv *RTv , int count)
{
	double		t[2];
	t_vector 	w;
	t_vector 	abc;

	w = minus_vectors(&RTv->camera, &RTv->shape[count].pos);
	abc.x = (ray->x * ray->x);
	abc.y = (2 * ray->y * w.y);
	abc.z = ((w.z * w.z) - (RTv->shape[count].r * RTv->shape[count].r));
	return (t_calculate(t, &abc));
}