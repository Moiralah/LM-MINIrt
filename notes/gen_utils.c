#include "minirt.h"

// Merges two sorted arrays of intersections.
void	sort(t_its **ori, t_its **l, t_its **r, int size)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while ((i + q) < size)
	{
		if (q >= ceil(size / 2))
			ori[i + q] = l[i];
		else if (i >= floor(size / 2))
			ori[q + i] = r[q];
		else if ((l[i]->len[0] < r[q]->len[0]) || (l[i]->len[1] < r[q]->len[1]))
			ori[i + q] = l[i];
		else
			ori[q + i] = r[q];
		if (q >= ceil(size / 2))
			i++;
		else if (i >= floor(size / 2))
			q++;
		else if ((l[i]->len[0] < r[q]->len[0]) || (l[i]->len[1] < r[q]->len[1]))
			i++;
		else
			q++;
	}
}

// Recursively merges and sorts an array of intersections.
t_its	**merge(t_its **ori, int size)
{
	t_its	**left;
	t_its	**right;
	int		mid;

	mid = floor(size / 2);
	if (mid == 0)
		return (ori);
	left = calloc(mid, sizeof(t_its *));
	if (!left)
		return (NULL);
	while (--mid >= 0)
		left[mid] = ori[mid];
	mid = ceil(size / 2);
	right = calloc(mid, sizeof(t_its *));
	if (!right)
		return (NULL);
	while (++mid <= size)
		right[size - mid] = ori[((int)floor(mid / 2)) + size - mid];
	left = merge(left, floor(size / 2));
	right = merge(right, floor(size / 2));
	sort(ori, left, right, size);
	free(left);
	free(right);
	return (ori);
}
