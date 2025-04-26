#include "minirt.h"

double	*cross(double *tuple1, double *tuple2, int size)
{
	double	*new_v;

	new_v = calloc(size, sizeof(double));
	new_v[0] = (tuple1[1] * tuple2[2]) - (tuple2[1] * tuple1[2]);
	new_v[1] = (tuple2[0] * tuple1[2]) - (tuple1[0] * tuple2[2]);
	new_v[2] = (tuple1[0] * tuple2[1]) - (tuple2[0] * tuple1[1]);
	return (new_v);
}

double	*schur(double *tuple1, double *tuple2, int size)
{
	double	*new_v;
	int		i;

	i = -1;
	new_v = calloc(size, sizeof(double));
	while (++i < size)
		new_v[i] = tuple1[i] * tuple2[i];
	return (new_v);
}

double	*norm(double *tuple, int size)
{
	double	*new_v;
	double	mag;
	int		i;

	i = -1;
	mag = magnitude(tuple, size);
	new_v = calloc(size, sizeof(double));
	while (++i < size)
		new_v[i] = tuple[i] / mag;
	return (new_v);
}

double	magnitude(double *tuple, int size)
{
	double	mag;
	int		i;

	mag = 0.0;
	i = -1;
	while (++i < size)
		mag += (tuple[i] * tuple[i]);
	return (sqrt(mag));
}

double	dot(double *tuple1, double *tuple2, int size)
{
	double	product;
	int		i;

	product = 0;
	i = -1;
	while (++i < size)
		product += (tuple1[i] * tuple2[i]);
	return (product);
}
