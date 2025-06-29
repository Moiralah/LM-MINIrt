#include "minirt.h"

// Computes the cross product of two 3D vectors.
double	*cross(double *tuple1, double *tuple2, int size)
{
	double	*new_v;

	new_v = calloc(size, sizeof(double));
	if (!new_v)
		return (NULL);
	new_v[0] = (tuple1[1] * tuple2[2]) - (tuple2[1] * tuple1[2]);
	new_v[1] = (tuple2[0] * tuple1[2]) - (tuple1[0] * tuple2[2]);
	new_v[2] = (tuple1[0] * tuple2[1]) - (tuple2[0] * tuple1[1]);
	return (new_v);
}

// Computes the element-wise (Hadamard) product of two vectors.
double	*schur(double *tuple1, double *tuple2, int size)
{
	double	*new_v;
	int		i;

	i = -1;
	new_v = calloc(size, sizeof(double));
	if (!new_v)
		return (NULL);
	while (++i < size)
		new_v[i] = tuple1[i] * tuple2[i];
	return (new_v);
}

// Normalizes a vector to have a magnitude of 1.
double	*norm(double *tuple, int size)
{
	double	*new_v;
	double	magnitude;
	int		i;

	i = -1;
	magnitude = mag(tuple, size);
	new_v = calloc(size, sizeof(double));
	if (!new_v)
		return (NULL);
	while (++i < size)
		new_v[i] = tuple[i] / magnitude;
	return (new_v);
}

// Computes the magnitude (length) of a vector.
double	mag(double *tuple, int size)
{
	double	mag;
	int		i;

	mag = 0.0;
	i = -1;
	while (++i < size)
		mag += (tuple[i] * tuple[i]);
	return (sqrt(mag));
}

// Computes the dot product of two vectors.
// Dot product = cosine of angle between them.
// Crucial for lighting, reflections, and refractions.
// It compute how light rays interact with surfaces.
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
