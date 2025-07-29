#include "minirt.h"

t_mat	*material(t_tuple *color, t_tuple *values)
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

t_mat	*copy_mat(t_mat *old)
{
	t_mat	*new;

	new = malloc(sizeof(t_mat));
	if (!new)
		return (NULL);
	new->color = copy_t(old->color);
	new->ambient = old->ambient;
	new->diffuse = old->diffuse;
	new->specular = old->specular;
	new->shininess = old->shininess;
	return (new);
}

/* double	spclr(t_tuple *reflect, t_tuple *eye, t_mat *mat, t_light *light)
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
	if (values[1] >= 0)
		diffuse(mat, m, temp, values);
	if (values[1] >= 0)
		values[3] = spclr(temp[1], m[1], mat, light);
	free_t(temp[1]);
	return ((values[0] * mat->ambient) + values[2] + values[3]);
} */

t_tuple	*lighting(t_mat *material, t_light *light, t_tuple **m, int shadowed)
{
	t_tuple	*lightv;
	t_tuple	*point;
	t_tuple	*eyev;
	t_tuple	*normalv;
	t_tuple	*reflectv;
	t_tuple	*effective_colour;
	t_tuple	*ambient;
	t_tuple	*diffuse;
	t_tuple	*specular;
	double	light_dot_normal;
	double	reflect_dot_eye;
	double	factor;

	point = m[0];
	eyev = m[1];
	normalv = m[2];
	effective_colour = schur(material->color, light->intensity);
	lightv = norm(sub(light->position, point));
	ambient = mult(effective_colour, material->ambient);
	if (shadowed)
		return (ambient);
	light_dot_normal = dot(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = tuple(3, 0.0, 0.0, 0.0);
		specular = tuple(3, 0.0, 0.0, 0.0);
	}
	else
	{
		diffuse = mult(effective_colour, (material->diffuse * light_dot_normal));
		reflectv = reflect(mult(lightv, -1), normalv);
		reflect_dot_eye = dot(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = tuple(3, 0.0, 0.0, 0.0);
		else
		{
			factor = pow(reflect_dot_eye, material->shininess);
			specular = mult(light->intensity, (material->specular * factor));
		}
	}
	return (add(add(ambient, diffuse), specular));
}

void	free_mat(t_mat *material)
{
	free_t(material->color);
	free(material);
}
