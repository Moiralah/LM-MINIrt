#include "minirt.h"

// Creates a list of intersections for a given size.
t_its	**its_s(int size, ...)
{
	t_its	**its_list;
	va_list	its_s;
	int		i;

	i = -1;
	its_list = calloc(size + 1, sizeof(t_its *));
	if (!its_list)
		return (NULL);
	va_start(its_s, size);
	while (++i < size)
		its_list[i] = va_arg(its_s, t_its *);
	its_list[i] = NULL;
	return (merge(its_list, i));
}

// Creates a new intersection object.
t_its	*its(t_obj *obj, double *len_from_ori, int cnt)
{
	t_its	*new_its;

	new_its = calloc(1, sizeof(t_its));
	new_its->obj = obj;
	new_its->len = len_from_ori;
	new_its->cnt = cnt;
	return (new_its);
}

// Finds the first positive intersection (hit).
t_its	*hit(t_its **its_s)
{
	int	i;

	i = 0;
	while ((its_s[i]) && (its_s[i]->len[0] <= 0))
		i++;
	return (its_s[i]);
}

// Frees the memory allocated for a list of intersections.
void	free_its_s(t_its **its_s)
{
	int	i;

	i = -1;
	while (its_s[++i])
		free_its(its_s[i]);
	free(its_s);
}

// Frees the memory allocated for a single intersection.
void	free_its(t_its *its)
{
	free(its->obj);
	free(its->len);
	free(its);
}
