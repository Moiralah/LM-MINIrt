#include "minirt.h"

t_obj	*sphere(t_tuple *origin, t_mat *mat, double radius)
{
	t_obj		*obj;
	t_sphere	*new_sphere;
	t_tuple		*w_ori;
	t_tuple		*move;
	t_tuple		**temp[2];

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!w_ori)
		return (NULL);
	move = sub(origin, w_ori);
	new_sphere = ft_calloc(1, sizeof(t_sphere));
	temp[0] = scale(4, radius, radius, radius);
	temp[1] = translate(4, move->val[0], move->val[1], move->val[2]);
	free_t(move);
	new_sphere->inv_tf = mxm(temp[1], temp[0]);
	free_m(temp[0], len_m(temp[0]));
	free_m(temp[1], len_m(temp[1]));
	new_sphere->mat = mat;
	new_sphere->ori = w_ori;
	new_sphere->rad = radius;
	obj = object(new_sphere, 'S');
	return (obj);
}

void	set_cy_transform(t_cylinder *cy, t_tuple **val_m, t_tuple *dim)
{
	t_tuple		**temp[2];
	t_tuple		*w_ori;
	t_tuple		*move;
	double		deg[3];

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!w_ori)
		return ;
	cy->ori = w_ori;
	move = sub(val_m[0], w_ori);
	deg[0] = val_m[1]->val[0] * 90;
	deg[1] = val_m[1]->val[1] * 90;
	deg[2] = val_m[1]->val[2] * 90;
	temp[0] = rotate(4, 3, deg[0], deg[1], deg[2]);
	temp[1] = scale(4, dim->val[0], dim->val[1], dim->val[0]);
	cy->inv_tf = mxm(temp[1], temp[0]);
	free_m(temp[0], len_m(temp[0]));
	free_m(temp[1], len_m(temp[1]));
	temp[0] = cy->inv_tf;
	temp[1] = translate(4, move->val[0], move->val[1], move->val[2]);
	free_t(move);
	cy->inv_tf = mxm(temp[1], cy->inv_tf);
	free_m(temp[0], len_m(temp[0]));
}

t_obj	*cylinder(t_tuple **val_m, t_mat *mat, t_tuple *dim, int closed)
{
	t_obj		*obj;
	t_cylinder	*new_cy;

	new_cy = ft_calloc(1, sizeof(t_cylinder));
	new_cy->mat = mat;
	new_cy->rad = dim->val[0];
	new_cy->h = dim->val[1];
	new_cy->max = dim->val[2];
	new_cy->min = dim->val[3];
	new_cy->closed = closed;
	set_cy_transform(new_cy, val_m, dim);
	obj = object(new_cy, 'C');
	return (obj);
}

t_obj	*plane(t_tuple *origin, t_mat *mat)
{
	t_plane	*p;
	t_obj	*obj;
	t_tuple	*w_ori;
	t_tuple	*move;

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	move = sub(origin, w_ori);
	p = ft_calloc(1, sizeof(t_plane));
	if (!p)
		return (NULL);
	p->inv_tf = translate(4, move->val[0], move->val[1], move->val[2]);
	free_t(move);
	p->ori = w_ori;
	p->mat = mat;
	obj = object(p, 'P');
	return (obj);
}
