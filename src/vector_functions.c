/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:32:25 by jjuntune          #+#    #+#             */
/*   Updated: 2022/06/16 17:59:19 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	m_a_vector(t_vector *a, t_vector *b)
{
	t_vector	new;
	double		ret;

	new.x = a->x * b->x;
	new.y = a->y * b->y;
	new.z = a->z * b->z;
	ret = (new.x + new.y + new.z);
	
	return (ret);
}

t_vector	*add_vectors(t_vector *a, t_vector *b)
{
	t_vector	*new;

	new = NULL;
	new->x = a->x + b->x;
	new->y = a->y + b->y;
	new->z = a->z + b->z;
	return (new);
}

t_vector	minus_vectors(t_vector *a, t_vector *b)
{
	t_vector	new;

	new.x = a->x - b->x;
	new.y = a->y - b->y;
	new.z = a->z - b->z;
	return (new);
}

t_vector	*multiply_vectors(t_vector *a, t_vector *b)
{
	t_vector	*new;

	new = NULL;
	new->x = a->x * b->x;
	new->y = a->y * b->y;
	new->z = a->z * b->z;
	return (new);
}

t_vector	*divide_vectors(t_vector *a, t_vector *b)
{
	t_vector	*new;

	new = NULL;
	new->x = a->x + b->x;
	new->y = a->y + b->y;
	new->z = a->z + b->z;
	return (new);
}
