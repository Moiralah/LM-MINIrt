/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 22:12:39 by huidris           #+#    #+#             */
/*   Updated: 2025/08/07 04:28:16 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*sphere(t_tuple *origin, t_mat *mat, double radius)
{
	t_obj		*obj;
	t_sphere	*new_sphere;
	t_tuple		**tf;
	t_tuple		*w_ori;
	t_tuple		*move;

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!w_ori)
		return (NULL);
	move = sub(origin, w_ori);
	new_sphere = ft_calloc(1, sizeof(t_sphere));
	new_sphere->mat = mat;
	new_sphere->ori = w_ori;
	new_sphere->rad = radius;
	new_sphere->inv_tf = NULL;
	obj = object(new_sphere, 'S');
	apply_tf(obj, scale(4, radius, radius, radius));
	apply_tf(obj, translate(4, move->val[0], move->val[1], move->val[2]));
	free_t(move);
	tf = new_sphere->inv_tf;
	new_sphere->inv_tf = inverse(new_sphere->inv_tf);
	free_m(tf, len_m(tf));
	return (obj);
}

void	set_cy_tf(t_obj *obj, t_tuple **val_m, t_tuple *w_ori, t_tuple *dim)
{
	t_tuple		*move;
	double		deg[3];

	deg[0] = val_m[1]->val[0] * M_PI;
	deg[1] = val_m[1]->val[1] * M_PI;
	deg[2] = val_m[1]->val[2] * M_PI;
	move = sub(val_m[0], w_ori);
	apply_tf(obj, scale(4, dim->val[0], dim->val[1], dim->val[0]));
	apply_tf(obj, rotate(4, 3, deg[0], deg[1], deg[2]));
	apply_tf(obj, translate(4, move->val[0], move->val[1], move->val[2]));
	free_t(move);
}

t_obj	*cylinder(t_tuple **val_m, t_mat *mat, t_tuple *dim, int closed)
{
	t_obj		*obj;
	t_cylinder	*new_cy;
	t_tuple		**tf;
	t_tuple		*w_ori;

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!w_ori)
		return (NULL);
	new_cy = ft_calloc(1, sizeof(t_cylinder));
	new_cy->ori = w_ori;
	new_cy->mat = mat;
	new_cy->rad = dim->val[0];
	new_cy->h = dim->val[1];
	new_cy->max = dim->val[2];
	new_cy->min = dim->val[3];
	new_cy->closed = closed;
	new_cy->inv_tf = NULL;
	obj = object(new_cy, 'C');
	set_cy_tf(obj, val_m, w_ori, dim);
	tf = new_cy->inv_tf;
	new_cy->inv_tf = inverse(new_cy->inv_tf);
	free_m(tf, len_m(tf));
	return (obj);
}

t_obj	*plane(t_tuple *origin, t_tuple *n, t_mat *mat)
{
	t_obj	*obj;
	t_plane	*p;
	t_tuple	**tf;
	t_tuple	*w_ori;
	t_tuple	*move;

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	move = sub(origin, w_ori);
	p = ft_calloc(1, sizeof(t_plane));
	if (!p)
		return (NULL);
	p->ori = w_ori;
	p->mat = mat;
	p->inv_tf = NULL;
	obj = object(p, 'P');
	apply_tf(obj, rotate(4, 3, n->val[0] * M_PI,
			n->val[1] * M_PI, n->val[2] * M_PI));
	apply_tf(obj, translate(4, move->val[0], move->val[1], move->val[2]));
	free_t(move);
	tf = p->inv_tf;
	p->inv_tf = inverse(p->inv_tf);
	free_m(tf, len_m(tf));
	return (obj);
}
