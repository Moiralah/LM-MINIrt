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
	if (obj->type == 'T')
		return (((t_test_shape *)(obj->data))->t_matrix);
	return (NULL);
}

t_tuple	*get_obj_ori(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->ori);
	// if (obj->type == 'P')
	// 	return (((t_plane *)(obj->data))->ori);
	// if (obj->type == 'C')
	// 	return (((t_cylinder *)(obj->data))->ori);
	return (NULL);
}

t_mat	*get_obj_mat(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->mat);
	// if (obj->type == 'P')
	// 	return (((t_plane *)(obj->data))->mat);
	// if (obj->type == 'C')
	// 	return (((t_cylinder *)(obj->data))->mat);
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
