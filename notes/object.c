#include "minirt.h"

t_obj	*object(void *data, char type)
{
	t_obj	*new_obj;

	new_obj = calloc(1, sizeof(t_obj));
	new_obj->data = data;
	new_obj->type = type;
	return (new_obj);
}

t_tuple	**get_obj_tf(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->t_matrix);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->t_matrix);
	if (obj->type == 'C')
		return (((t_cylinder *)(obj->data))->t_matrix);
	return (NULL);
}

t_tuple	*get_obj_ori(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->ori);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->ori);
	if (obj->type == 'C')
		return (((t_cylinder *)(obj->data))->ori);
	return (NULL);
}

t_mat	*get_obj_mat(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->mat);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->mat);
	if (obj->type == 'C')
		return (((t_cylinder *)(obj->data))->mat);
	return (NULL);
}

t_sphere	*sphere(t_tuple *origin, t_mat *mat, double radius)
{
	t_sphere	*new_sphere;

	new_sphere = calloc(1, sizeof(t_sphere));
	new_sphere->t_matrix = identity(origin->size);
	new_sphere->mat = mat;
	new_sphere->ori = origin;
	new_sphere->rad = radius;
	return (new_sphere);
}

t_cylinder	*cylinder(t_tuple *origin, t_mat *mat, double rad, double h)
{
	t_cylinder	*new_cy;
	t_tuple		**temp[2];
	t_tuple		*w_ori;
	t_tuple		*move;

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!w_ori)
		return (NULL);
	move = sub(origin, w_ori);
	if (!move)
		return (NULL);
	new_cy = calloc(1, sizeof(t_cylinder));
	new_cy->t_matrix = translate(4, move->val[0], move->val[1], move->val[2]);
	if (!new_cy->t_matrix)
		return (NULL);
	temp[0] = new_cy->t_matrix;
	temp[1] = scale(4, rad, h, rad);
	new_cy->t_matrix = mxm(temp[1], new_cy->t_matrix);
	free_m(temp[0], len_m(temp[0]));
	free_m(temp[1], len_m(temp[1]));
	new_cy->mat = mat;
	new_cy->ori = w_ori;
	new_cy->rad = rad;
	new_cy->max = 1.0; 
	new_cy->min = -1.0;
	new_cy->h = h;
	new_cy->closed = 1;
	return (new_cy);
}
