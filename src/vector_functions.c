/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:32:25 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/12 16:03:12 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	dot_prdct(t_vector a, t_vector b)
{
	t_vector	new;
	double		ret;

	new.x = a.x * b.x;
	new.y = a.y * b.y;
	new.z = a.z * b.z;
	ret = (new.x + new.y + new.z);
	return (ret);
}

t_vector	add_vectors(t_vector a, t_vector b)
{
	t_vector	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

t_vector	minus_vectors(t_vector a, t_vector b)
{
	t_vector	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}

t_vector	multiply_vectors(t_vector a, t_vector b)
{
	t_vector	new;

	new.x = a.x * b.x;
	new.y = a.y * b.y;
	new.z = a.z * b.z;
	return (new);
}

t_vector	divide_vectors(t_vector a, t_vector b)
{
	t_vector	new;

	if (a.x == 0.0f && b.x == 0.0f)
		new.x = 0;
	else
		new.x = a.x / b.x;
	if (a.y == 0.0f && b.y == 0.0f)
		new.y = 0;
	else
		new.y = a.y / b.y;
	if (a.z == 0.0f && b.z == 0.0f)
		new.z = 0;
	else
		new.z = a.z / b.z;
	return (new);
}
