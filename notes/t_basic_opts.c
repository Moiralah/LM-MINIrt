#include "minirt.h"

// Multiplies each element of a vector by a scalar value.
double	*mult(double *tuple, double value, int size)
{
	double	*new_v;
	int		i;

	i = -1;
	new_v = calloc(size, sizeof(double));
	if (!new_v)
		return (NULL);
	while (++i < size)
		new_v[i] = tuple[i] * value;
	return (new_v);
}

// Subtracts one vector from another element-wise.
double	*sub(double *tuple1, double *tuple2, int size)
{
	double	*new_v;
	int		i;

	i = -1;
	new_v = calloc(size, sizeof(double));
	if (!new_v)
		return (NULL);
	while (++i < size)
		new_v[i] = tuple1[i] - tuple2[i];
	return (new_v);
}

// Adds two vectors element-wise.
double	*add(double *tuple1, double *tuple2, int size)
{
	double	*new_v;
	int		i;

	i = -1;
	new_v = calloc(size, sizeof(double));
	if (!new_v)
		return (NULL);
	while (++i < size)
		new_v[i] = tuple1[i] + tuple2[i];
	return (new_v);
}
