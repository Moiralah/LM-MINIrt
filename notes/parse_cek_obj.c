#include "minirt.h"

void	check_sphere(t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	while (data->data[i])
	{
		if (check_char(data->data[i], "sp ") == 1)
		{
			temp = ft_split(data->data[i], ' ');
			if (ft_arraylen(temp) != 8)
			{
				free2d(temp);
				return (perr("Error: Format: 'sp <x,y,z> <sp dia.> <R,G,B>'."),
					exit(1));
			}
			check_range(0, 255, ft_atof(temp[5]));
			check_range(0, 255, ft_atof(temp[6]));
			check_range(0, 255, ft_atof(temp[7]));
			free2d(temp);
		}
		i++;
	}
}

void	check_plane(t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	while (data->data[i])
	{
		if (check_char(data->data[i], "pl ") == 1)
		{
			temp = ft_split(data->data[i], ' ');
			if (ft_arraylen(temp) != 10)
			{
				free2d(temp);
				return (perr("Error:Format:'pl <x,y,z> <x,y,z> <R,G,B>'."),
					exit(1));
			}
			check_range(-1, 1, ft_atof(temp[4]));
			check_range(-1, 1, ft_atof(temp[5]));
			check_range(-1, 1, ft_atof(temp[6]));
			check_range(0, 255, ft_atof(temp[7]));
			check_range(0, 255, ft_atof(temp[8]));
			check_range(0, 255, ft_atof(temp[9]));
			free2d(temp);
		}
		i++;
	}
}

#define CY "Error: Format:'cy <x,y,z> <x,y,z> <cy dia.> <cy height> <R,G,B>'."

void	check_cylinder(t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	while (data->data[i])
	{
		if (check_char(data->data[i], "cy ") == 1)
		{
			temp = ft_split(data->data[i], ' ');
			if (ft_arraylen(temp) != 12)
			{
				free2d(temp);
				return (perr(CY), exit(1));
			}
			check_range(-1, 1, ft_atof(temp[4]));
			check_range(-1, 1, ft_atof(temp[5]));
			check_range(-1, 1, ft_atof(temp[6]));
			check_range(0, 255, ft_atof(temp[9]));
			check_range(0, 255, ft_atof(temp[10]));
			check_range(0, 255, ft_atof(temp[11]));
			free2d(temp);
		}
		i++;
	}
}
