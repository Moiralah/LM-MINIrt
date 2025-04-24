#include "minirt.h"

double	*mult(double *vector, double value, int size)
{
	double	*newVector;
	int	i;

	i = -1;
	newVector = calloc(size, sizeof(double));
	while (++i < size)
		newVector[i] = vector[i] * value;
	return (newVector);
}

double	*sub(double *vector1, double *vector2, int size)
{
	double	*newVector;
	int	i;

	i = -1;
	newVector = calloc(size, sizeof(double));
	while (++i < size)
		newVector[i] = vector1[i] - vector2[i];
	return (newVector);
}

double	*add(double *vector1, double *vector2, int size)
{
	double	*newVector;
	int	i;

	i = -1;
	newVector = calloc(size, sizeof(double));
	while (++i < size)
		newVector[i] = vector1[i] + vector2[i];
	return (newVector);
}

void	printVector(double *vector, int size)
{
	int	i;

	i = -1;
	printf("[");
	while (++i < (size - 1))
		printf("%f ", vector[i]);
	printf("%f]\n", vector[i]);
}
