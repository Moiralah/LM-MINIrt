#include "minirt.h"

t_mat	*material(int color, t_tuple *values)
{
	t_mat	*material;

	material = malloc(sizeof(t_mat));
	if (!material)
		return (NULL);
	material->color = color;
	material->ambient = values->val[0];
	material->diffuse = values->val[1];
	material->specular = values->val[2];
	material->shininess = values->val[3];
	return (material);
}

double	spclr(t_tuple *reflect, t_tuple *eye, t_mat *mat, t_light *light)
{
	double	reflect_dot_eye;
	double	factor;
	double	specular;

	reflect_dot_eye = dot(reflect, eye);
	if (reflect_dot_eye <= 0)
		specular = 0.0;
	else
	{
		factor = pow(reflect_dot_eye, mat->shininess);
		specular = light->intensity * mat->specular * factor;
	}
	return (specular);
}

void	diffuse(t_mat *mat, t_tuple **m, t_tuple **temp, double *values)
{
	if (values[1] >= 0)
		values[2] = values[0] * mat->diffuse * values[1];
	free_t(temp[0]);
	temp[0] = mult(temp[1], -1.0);
	if (!temp[0])
		return (free_t(temp[1]));
	free_t(temp[1]);
	temp[1] = reflect(temp[0], m[2]);
	if (!temp[1])
		return (free_t(temp[0]));
	free_t(temp[0]);
}

int	lighting(t_mat *mat, t_light *light, t_tuple **m)
{
	t_tuple	*temp[2];
	double	values[4];

	temp[0] = sub(light->position, m[0]);
	if (!temp[0])
		return (-1);
	temp[1] = norm(temp[0]);
	if (!temp[1])
		return (free_t(temp[0]), -1);
	values[0] = mat->color * light->intensity;
	values[1] = dot(temp[1], m[2]);
	values[2] = 0.0;
	values[3] = 0.0;
	diffuse(mat, m, temp, values);
	values[3] = spclr(temp[1], m[1], mat, light);
	free_t(temp[1]);
	return ((values[0] * mat->ambient) + values[2] + values[3]);
}
