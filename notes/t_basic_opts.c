#include "minirt.h"

// Multiplies each element of a vector by a scalar value.
t_tuple	*mult(t_tuple *tuple, double value)
{
	t_tuple	*new_v;
	int		i;

	i = -1;
	new_v = calloc(tuple->size, sizeof(t_tuple));
	if (!new_v)
		return (NULL);
	while (++i < tuple->size)
		new_v->val[i] = tuple->val[i] * value;
	return (new_v);
}

// Subtracts one vector from another element-wise.
t_tuple	*sub(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*new_v;
	int		i;

	i = -1;
	if (tuple1->size != tuple2->size)
		return (NULL);
	new_v = calloc(tuple1->size, sizeof(t_tuple));
	if (!new_v)
		return (NULL);
	while (++i < tuple1->size)
		new_v->val[i] = tuple1->val[i] - tuple2->val[i];
	return (new_v);
}

// Adds two vectors element-wise.
t_tuple	*add(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*new_v;
	int		i;

	i = -1;
	if (tuple1->size != tuple2->size)
		return (NULL);
	new_v = calloc(tuple1->size, sizeof(t_tuple));
	if (!new_v)
		return (NULL);
	while (++i < tuple1->size)
		new_v->val[i] = tuple1->val[i] + tuple2->val[i];
	return (new_v);
}
