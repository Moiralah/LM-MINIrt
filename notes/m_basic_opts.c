#include "minirt.h"

void	mult_m(t_tuple **m, double value)
{
	double	*product;
	int		row;

	row = -1;
	while (m[++row])
	{
		product = mult(m[row]->val, value, m[row]->size);
		free(m[row]->val);
		m[row]->val = product;
	}
}
