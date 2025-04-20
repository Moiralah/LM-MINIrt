#include "minirt.h"

#include <stdio.h>

float ft_atof(const char *str)
{
    int i = 0;
    float num = 0.0f; // Use float for the result
    int sign = 1;

    // Skip whitespace characters
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;

    // Handle optional sign
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    // Process digits before the decimal point
    while (str[i] >= '0' && str[i] <= '9')
    {
        num = num * 10.0f + (str[i] - '0'); // Maintain floating-point precision
        i++;
    }

    // Handle decimal point and fractional part
    if (str[i] == '.')
    {
        i++;
        float fraction = 1.0f; // To handle fractional values
        while (str[i] >= '0' && str[i] <= '9')
        {
            fraction /= 10.0f;               // Scale down by 10 for each digit
            num += (str[i] - '0') * fraction; // Add fractional part
            i++;
        }
    }

    return num * sign; // Apply the sign and return as float
}

int main (int ac, char **av)
{
	t_tuple	tuple;

	if (ac < 5)
		return (0);

	tuple = (t_tuple){0};
	tuple.w = ft_atof(av[1]);
	tuple.x = ft_atof(av[2]);
	tuple.y = ft_atof(av[3]);
	tuple.z = ft_atof(av[4]);

	printf("Tuple (%f %f %f %f)\n", tuple.w, tuple.x, tuple.y, tuple.z);
}

