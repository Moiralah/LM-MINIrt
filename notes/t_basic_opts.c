#include "minirt.h"

double	*mult(double *tuple, double value, int size)
{
	double	*new_v;
	int		i;

	i = -1;
	new_v = calloc(size, sizeof(double));
	while (++i < size)
		new_v[i] = tuple[i] * value;
	return (new_v);
}

double	*sub(double *tuple1, double *tuple2, int size)
{
	double	*new_v;
	int		i;

	i = -1;
	new_v = calloc(size, sizeof(double));
	while (++i < size)
		new_v[i] = tuple1[i] - tuple2[i];
	return (new_v);
}

double	*add(double *tuple1, double *tuple2, int size)
{
	double	*new_v;
	int		i;

	i = -1;
	new_v = calloc(size, sizeof(double));
	while (++i < size)
		new_v[i] = tuple1[i] + tuple2[i];
	return (new_v);
}
