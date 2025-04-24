#include "minirt.h"

double	*cross(double *vector1, double *vector2, int size)
{
	double	*newVector;

	newVector = calloc(size, sizeof(double));
	newVector[0] = (vector1[1] * vector2[2]) - (vector2[1] * vector1[2]);
	newVector[1] = (vector2[0] * vector1[2]) - (vector1[0] * vector2[2]);
	newVector[2] = (vector1[0] * vector2[1]) - (vector2[0] * vector1[1]);
	return (newVector);
}

double	*schur(double *vector1, double *vector2, int size)
{
	double	*newVector;
	int	i;

	i = -1;
	newVector = calloc(size, sizeof(double));
	while (++i < size)
		newVector[i] = vector1[i] * vector2[i];
	return (newVector);
}

double	*norm(double *vector, int size)
{
	double	*newVector;
	double	mag;
	int	i;

	i = -1;
	mag = magnitude(vector, size);
	newVector = calloc(size, sizeof(double));
	while (++i < size)
		newVector[i] = vector[i] / mag;
	return (newVector);
}

double	magnitude(double *vector, int size)
{
	double	mag;
	int	i;

	mag = 0.0;
	i = -1;
	while (++i < size)
		mag += (vector[i] * vector[i]);
	return (sqrt(mag));
}

double	dot(double *vector1, double *vector2, int size)
{
	double	product;
	int	i;

	product = 0;
	i = -1;
	while (++i < size)
		product += (vector1[i] * vector2[i]);
	return (product);
}
