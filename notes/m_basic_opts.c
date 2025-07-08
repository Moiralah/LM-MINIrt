#include "minirt.h"

// Multiplies each element of a matrix by a scalar value.
void	mult_m(t_tuple **m, double value)
{
	t_tuple	*product;
	int		row;

	row = -1;
	while (m[++row])
	{
		product = mult(m[row], value);
		free_t(m[row]);
		m[row] = product;
	}
}
