#include "minirt.h"

void	set_sphere(char *line, t_data *data)
{
	char	**temp;
	t_sp	*new_sp;
	t_sp	*cur_sp;

	temp = ft_split(line, ' ');
	new_sp = malloc(sizeof(t_sp));
	new_sp->sp_centre = tuple(3, ft_atof(temp[1]),
			ft_atof(temp[2]), ft_atof(temp[3]));
	new_sp->sp_diameter = ft_atof(temp[4]);
	new_sp->sp_color = tuple(3, ft_atof(temp[5]),
			ft_atof(temp[6]), ft_atof(temp[7]));
	new_sp->next = NULL;
	if (!data->sphere)
		data->sphere = new_sp;
	else
	{
		cur_sp = data->sphere;
		while (cur_sp->next)
			cur_sp = cur_sp->next;
		cur_sp->next = new_sp;
	}
	free2d(temp);
}

void	set_plane(char *line, t_data *data)
{
	char	**temp;
	t_pl	*new_pl;
	t_pl	*cur_pl;

	temp = ft_split(line, ' ');
	new_pl = malloc(sizeof(t_pl));
	new_pl->pl_point = tuple(3, ft_atof(temp[1]),
			ft_atof(temp[2]), ft_atof(temp[3]));
	new_pl->pl_normalv = tuple(3, ft_atof(temp[4]),
			ft_atof(temp[5]), ft_atof(temp[6]));
	new_pl->pl_color = tuple(3, ft_atof(temp[7]),
			ft_atof(temp[8]), ft_atof(temp[9]));
	new_pl->next = NULL;
	if (!data->plane)
		data->plane = new_pl;
	else
	{
		cur_pl = data->plane;
		while (cur_pl->next)
			cur_pl = cur_pl->next;
		cur_pl->next = new_pl;
	}
	free2d(temp);
}

void	set_cylinder(char *line, t_data *data)
{
	char	**temp;
	t_cy	*new_cy;
	t_cy	*cur_cy;

	temp = ft_split(line, ' ');
	new_cy = malloc(sizeof(t_cy));
	new_cy->cy_centre = tuple(3, ft_atof(temp[1]),
			ft_atof(temp[2]), ft_atof(temp[3]));
	new_cy->cy_normalv = tuple(3, ft_atof(temp[4]),
			ft_atof(temp[5]), ft_atof(temp[6]));
	new_cy->cy_diameter = ft_atof(temp[7]);
	new_cy->cy_height = ft_atof(temp[8]);
	new_cy->cy_color = tuple(3, ft_atof(temp[9]),
			ft_atof(temp[10]), ft_atof(temp[11]));
	new_cy->next = NULL;
	if (!data->cylinder)
		data->cylinder = new_cy;
	else
	{
		cur_cy = data->cylinder;
		while (cur_cy->next)
			cur_cy = cur_cy->next;
		cur_cy->next = new_cy;
	}
	free2d(temp);
}
