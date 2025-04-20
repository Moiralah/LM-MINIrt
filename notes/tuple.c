#include <stdio.h>
#include "minirt.h"

float	ft_atof(const char *str)
{
	int		i;
	float	num;
	float	fraction;
	char	**numint;

	numint = ft_split(str, '.');
	num = 0.0f + ft_atoi(numint[0]);
	i = 0;
	fraction = 1.0f;
	if (numint[1] == NULL)
		return (num);
	while (numint[1][i] >= '0' && numint[1][i] <= '9')
	{
		fraction /= 10.0f;
		num += (numint[1][i++] - '0') * fraction;
	}
	return (num);
}
/*
int main(int ac, char **av)
{
	t_tuple tuple;

	if (ac < 5)
		return (0);

	tuple = (t_tuple){0};
	tuple.w = ft_atof(av[1]);
	tuple.x = ft_atof(av[2]);
	tuple.y = ft_atof(av[3]);
	tuple.z = ft_atof(av[4]);
	printf("Tuple (%f %f %f %f)\n", tuple.w, tuple.x, tuple.y, tuple.z);
}
*/

// int main()
// {
// 	char x[] = "34.89";
// 	char y[] = "34.0000";
// 	char z[] = "34.9789";
// 	char w[] = "1.yuag";
// 	float tuplex, tupley, tuplez, tuplew;

// 	tuplew = ft_atof(w);
// 	tuplex = ft_atof(x);
// 	tupley = ft_atof(y);
// 	tuplez = ft_atof(z);

// 	printf("Tuple (%f %f %f %f)\n", tuplew, tuplex, tupley, tuplez);
// }
