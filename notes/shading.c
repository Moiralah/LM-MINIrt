#include "minirt.h"

t_tuple	*reflect(t_tuple *in, t_tuple *normal)
{
	double	dot_product;

	dot_product = dot(in->val, normal->val, 4);
	return (sub(in->val, mult(normal->val, 2 * dot_product, 4), 4));
}

t_light	*light(t_tuple *position, int intensity)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = position;
	light->intensity = intensity;
	return (light);
}

t_material	*material(int color, double ambient, double diffuse, double specular, double shininess)
{
	t_material	*material;

	material = malloc(sizeof(t_material));
	if (!material)
		return (NULL);
	material->color = color;
	material->ambient = ambient;
	material->diffuse = diffuse;
	material->specular = specular;
	material->shininess = shininess;
	return (material);
}

// int lighting(t_material *material, t_light *light, t_tuple *point, t_tuple *eye, t_tuple *normal)
// {
// 	double	effective_color;
// 	double	*lightv;
// 	double	ambient;
// 	double	light_dot_normal;
// 	double	diffuse;
// 	double	specular;
// 	double	reflect_dot_eye;
// 	double	factor;
// 	t_tuple	*reflectv;

// 	effective_color = material->color * light->intensity;
// 	lightv = norm(sub(light->position, point->val, 4), 4);
// 	ambient = effective_color * material->ambient;
// 	light_dot_normal = dot(lightv, normal->val, 4);
// 	if (light_dot_normal < 0)
// 	{
// 		diffuse = 0.0;
// 		specular = 0.0;
// 	}
// 	else
// 		diffuse = effective_color * material->diffuse * light_dot_normal;
// 	reflectv = reflect(mult(lightv, -1.0, 4), normal);
// 	reflect_dot_eye = dot(reflectv->val, eye->val, 4);
// 	if (reflect_dot_eye <= 0)
// 		specular = 0.0;
// 	else
// 	{
// 		factor = pow(reflect_dot_eye, material->shininess);
// 		specular = light->intensity * material->specular * factor;
// 	}
// 	return (ambient + diffuse + specular);
// }

double	specula(t_tuple *reflectv, t_tuple *eye, t_material *material, t_light *light)
{
	double	reflect_dot_eye;
	double	factor;
	double	specular;

	reflect_dot_eye = dot(reflectv->val, eye->val, 4);
	if (reflect_dot_eye <= 0)
		specular = 0.0;
	else
	{
		factor = pow(reflect_dot_eye, material->shininess);
		specular = light->intensity * material->specular * factor;
	}
	return (specular);
}

int	lighting(t_material *material, t_light *light, t_tuple *point, t_tuple *eye, t_tuple *normal)
{
	double	effective_color;
	double	*lightv;
	double	light_dot_normal;
	double	diffuse;
	double	specular;

	effective_color = material->color * light->intensity;
	lightv = norm(sub(light->position, point->val, 4), 4);
	light_dot_normal = dot(lightv, normal->val, 4);
	if (light_dot_normal < 0)
	{
		diffuse = 0.0;
		specular = 0.0;
	}
	else
		diffuse = effective_color * material->diffuse * light_dot_normal;
	specular = specula(reflect(mult(lightv, -1.0, 4), normal),
			eye, material, light);
	return ((effective_color * material->ambient) + diffuse + specular);
}
