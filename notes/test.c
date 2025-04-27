#include "minirt.h"

int	main(void)
{
	t_tuple	**m1;
	t_tuple	**m2;
	t_tuple	**m3;
	t_tuple	*t1;
	t_tuple	*t2;
	t_tuple	*t3;
	t_tuple	*t4;
	t_tuple	*t5;
	t_tuple	*t6;
	t_tuple	*t7;
	t_tuple	*t8;

	t1 = tuple(4, 2.2, 5.2, 4.3, 9.8);
	t2 = tuple(4, 7.3, 0.1, 3.4, 2.7);
	t3 = tuple(4, 3.4, 6.4, 1.5, 6.5);
	t4 = tuple(4, 4.5, 9.2, 8.7, 5.9);
	m1 = matrix(5, t1, t2, t3, t4);
	t5 = tuple(4, 3.0, 0.0, -1.0, 5.0);
	t6 = tuple(4, 1.0, 2.0, 9.0, 4.0);
	t7 = tuple(4, 5.0, 4.0, 3.0, 3.0);
	t8 = tuple(4, 9.0, 3.0, 8.0, 6.0);
	m2 = matrix(5, t5, t6, t7, t8);
	m3 = inverse(m1);
	print_m(m3);
	free_m(m1, len_m(m1));
	free_m(m2, len_m(m2));
	free_m(m3, len_m(m3));
	return (0);
}
