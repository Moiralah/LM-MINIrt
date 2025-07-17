#include "minirt.h"

// //Merges two sorted arrays of intersections.
// void	sort(t_its **ori, t_its **l, t_its **r, int size)
// {
// 	int	i;
// 	int	q;

// 	i = 0;
// 	q = 0;
// 	while ((i + q) < size)
// 	{
// 		if (q >= ceil(size / 2))
// 			ori[i + q] = l[i];
// 		else if (i >= floor(size / 2))
// 			ori[q + i] = r[q];
// 		else if ((l[i]->len[0] < r[q]->len[0]) || (l[i]->len[1] < r[q]->len[1]))
// 			ori[i + q] = l[i];
// 		else
// 			ori[q + i] = r[q];
// 		if (q >= ceil(size / 2))
// 			i++;
// 		else if (i >= floor(size / 2))
// 			q++;
// 		else if ((l[i]->len[0] < r[q]->len[0]) || (l[i]->len[1] < r[q]->len[1]))
// 			i++;
// 		else
// 			q++;
// 	}
// }

// // Recursively merges and sorts an array of intersections.
// t_its	**merge(t_its **ori, int size)
// {
// 	t_its	**left;
// 	t_its	**right;
// 	int		mid;

// 	mid = floor(size / 2);
// 	if (mid == 0)
// 		return (ori);
// 	left = calloc(mid, sizeof(t_its *));
// 	if (!left)
// 		return (NULL);
// 	while (--mid >= 0)
// 		left[mid] = ori[mid];
// 	mid = ceil(size / 2);
// 	right = calloc(mid, sizeof(t_its *));
// 	if (!right)
// 		return (NULL);
// 	while (++mid <= size)
// 		right[size - mid] = ori[((int)floor(mid / 2)) + size - mid];
// 	left = merge(left, floor(size / 2));
// 	right = merge(right, floor(size / 2));
// 	sort(ori, left, right, size);
// 	free(left);
// 	free(right);
// 	return (ori);
// }

/// ignore--------------------------------

void sort(t_its **dest, t_its **left, t_its **right, int size)
{
	int mid = size / 2;
	int left_size = mid;
	int right_size = size - mid;
	int i = 0, j = 0, k = 0;

	while (i < left_size && j < right_size)
	{
		if (left[i]->len[0] <= right[j]->len[0])
			dest[k++] = left[i++];
		else
			dest[k++] = right[j++];
	}
	while (i < left_size)
		dest[k++] = left[i++];
	while (j < right_size)
		dest[k++] = right[j++];
}

t_its **merge(t_its **arr, int size)
{
	if (size <= 1)
		return arr;

	int mid = size / 2;

	t_its **left = malloc(mid * sizeof(t_its *));
	t_its **right = malloc((size - mid) * sizeof(t_its *));

	if (!left || !right)
		return NULL; // handle allocation failure

	for (int i = 0; i < mid; i++)
		left[i] = arr[i];
	for (int i = 0; i < size - mid; i++)
		right[i] = arr[i + mid];

	merge(left, mid);
	merge(right, size - mid);

	sort(arr, left, right, size);

	free(left);
	free(right);

	return arr;
}
