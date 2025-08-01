#include "minirt.h"

/* t_its	**intersect(t_ray *ray, t_obj *obj)
{
	if (obj->type == 'S')
		return (sphere_its(obj, ray));
	else if (obj->type == 'P')
		return (plane_its(obj, ray));
	else if (obj->type == 'C')
	 	return (cylinder_its(obj, ray));
	return (NULL);
} */

t_tuple	*transform_ori(t_tuple **t_matrix, t_tuple *ori)
{
	t_tuple	**result_m;
	t_tuple	**temp_m;
	t_tuple	**trans;
	t_tuple	*new_ori;

	temp_m = matrix(2, ori);
	if (!temp_m)
		return (NULL);
	if (!t_matrix)
		return (free(temp_m), NULL);
	trans = transpose(temp_m);
	if (!trans)
		return (free(temp_m), NULL);
	result_m = mxm(t_matrix, trans);
	if (!result_m)
		return (free(temp_m), NULL);
	free(temp_m);
	temp_m = transpose(result_m);
	if (!temp_m)
		return (NULL);
	free_m(result_m, len_m(result_m));
	free_m(trans, len_m(trans));
	new_ori = temp_m[0];
	return (free(temp_m), new_ori);
}

t_tuple	*transform_dir(t_tuple **t_matrix, t_tuple *dir)
{
	t_tuple	**result_m;
	t_tuple	**temp_m;
	t_tuple	**trans;
	t_tuple	*new_dir;

	temp_m = matrix(2, dir);
	if (!temp_m)
		return (NULL);
	if (!t_matrix)
		return (free(temp_m), NULL);
	trans = transpose(temp_m);
	if (!trans)
		return (free(temp_m), NULL);
	result_m = mxm(t_matrix, trans);
	if (!result_m)
		return (free(temp_m), NULL);
	free(temp_m);
	temp_m = transpose(result_m);
	if (!temp_m)
		return (NULL);
	free_m(result_m, len_m(result_m));
	free_m(trans, len_m(trans));
	new_dir = temp_m[0];
	return (free(temp_m), new_dir);
}

// Calculates the position of a ray at a given time.
t_tuple	*travel(t_ray *ray, double time)
{
	t_tuple	*velo;
	t_tuple	*new_pos;

	velo = mult(ray->dir, time);
	new_pos = add(ray->ori, velo);
	free_t(velo);
	return (new_pos);
}
