#include "minirt.h"

t_obj	*object(void *data, char type)
{
	t_obj	*new_obj;

	new_obj = calloc(1, sizeof(t_obj));
	new_obj->data = data;
	new_obj->type = type;
	return (new_obj);
}

t_sphere	*sphere(t_tuple *origin, double radius)
{
	t_sphere	*new_sphere;

	new_sphere = calloc(1, sizeof(t_sphere));
	new_sphere->t_matrix = identity(origin->size);
	new_sphere->ori = origin;
	new_sphere->rad = radius;
	return (new_sphere);
}
