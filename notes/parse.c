#include "minirt.h"

#define BUFFER_SIZE 4096

t_scene *parse_rt_file(const char *filename)
{
	int fd;
	char buffer[BUFFER_SIZE + 1];
	char *file_content = NULL;
	char *temp;
	ssize_t bytes_read;
	char **lines;
	t_scene *scene;

	// Validate file extension
	if (!ft_strnstr(filename, ".rt", ft_strlen(filename)))
	{
		printf("Error: Invalid file extension. Expected .rt\n");
		return (NULL);
	}

	// Open the file
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}

	// Read the file into a buffer
	file_content = ft_strdup("");
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = file_content;
		file_content = ft_strjoin(file_content, buffer);
		free(temp);
		if (!file_content)
		{
			close(fd);
			return (NULL);
		}
	}
	if (bytes_read < 0)
	{
		perror("Error reading file");
		free(file_content);
		close(fd);
		return (NULL);
	}
	close(fd);

	// Split the file content into lines
	lines = ft_split(file_content, '\n');
	free(file_content);
	if (!lines)
		return (NULL);

	// Initialize the scene
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
	{
		ft_free_array(lines);
		return (NULL);
	}

	// Parse each line
	for (int i = 0; lines[i]; i++)
	{
		if (ft_strncmp(lines[i], "A ", 2) == 0)
			parse_ambient(scene, lines[i]);
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
			parse_camera(scene, lines[i]);
		else if (ft_strncmp(lines[i], "L ", 2) == 0)
			parse_light(scene, lines[i]);
		else if (ft_strncmp(lines[i], "sp ", 3) == 0 || ft_strncmp(lines[i], "pl ", 3) == 0 || ft_strncmp(lines[i], "cy ", 3) == 0)
			parse_object(scene, lines[i]);
		else if (lines[i][0] != '\0') // Ignore empty lines
			printf("Warning: Unknown identifier in line: %s\n", lines[i]);
	}

	// Free the lines array
	ft_free_array(lines);

	return (scene);
}

void free_scene(t_scene *scene)
{
	if (!scene)
		return;

	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
	{
		free_t(scene->camera->position);
		free_t(scene->camera->orientation);
		free(scene->camera);
	}
	if (scene->light)
	{
		free_t(scene->light->position);
		free(scene->light);
	}
	while (scene->objects)
	{
		t_object *temp = scene->objects;
		scene->objects = scene->objects->next;
		free_t(temp->position);
		if (temp->orientation)
			free_t(temp->orientation);
		free(temp);
	}
	free(scene);
}

void parse_ambient(t_scene *scene, char *line)
{
	char **tokens = ft_split(line, ' ');

	if (!tokens || ft_arraylen(tokens) != 3)
	{
		printf("Error: Invalid ambient lighting format\n");
		return;
	}

	scene->ambient = ft_calloc(1, sizeof(t_ambient));
	if (!scene->ambient)
		return;

	scene->ambient->ratio = ft_atof(tokens[1]);
	scene->ambient->color = parse_color(tokens[2]);

	ft_free_array(tokens);
}

void parse_camera(t_scene *scene, char *line)
{
	char **tokens = ft_split(line, ' ');

	if (!tokens || ft_arraylen(tokens) != 4)
	{
		printf("Error: Invalid camera format\n");
		return;
	}

	scene->camera = ft_calloc(1, sizeof(t_camera));
	if (!scene->camera)
		return;

	scene->camera->position = parse_tuple(tokens[1]);
	scene->camera->orientation = parse_tuple(tokens[2]);
	scene->camera->fov = ft_atof(tokens[3]);

	ft_free_array(tokens);
}

void parse_light(t_scene *scene, char *line)
{
	char **tokens = ft_split(line, ' ');

	if (!tokens || ft_arraylen(tokens) != 4)
	{
		printf("Error: Invalid light format\n");
		return;
	}

	scene->light = ft_calloc(1, sizeof(t_light));
	if (!scene->light)
		return;

	scene->light->position = parse_tuple(tokens[1]);
	scene->light->brightness = ft_atof(tokens[2]);
	scene->light->color = parse_color(tokens[3]);

	ft_free_array(tokens);
}

void parse_object(t_scene *scene, char *line)
{
	char **tokens = ft_split(line, ' ');

	if (!tokens)
	{
		printf("Error: Invalid object format\n");
		return;
	}

	t_object *obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return;

	obj->type = ft_strdup(tokens[0]);
	obj->position = parse_tuple(tokens[1]);
	if (ft_strncmp(obj->type, "sp", 2) == 0)
	{
		obj->diameter = ft_atof(tokens[2]);
		obj->color = parse_color(tokens[3]);
	}
	else if (ft_strncmp(obj->type, "pl", 2) == 0)
	{
		obj->orientation = parse_tuple(tokens[2]);
		obj->color = parse_color(tokens[3]);
	}
	else if (ft_strncmp(obj->type, "cy", 2) == 0)
	{
		obj->orientation = parse_tuple(tokens[2]);
		obj->diameter = ft_atof(tokens[3]);
		obj->height = ft_atof(tokens[4]);
		obj->color = parse_color(tokens[5]);
	}

	obj->next = scene->objects;
	scene->objects = obj;

	ft_free_array(tokens);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <scene.rt>\n", argv[0]);
		return (1);
	}

	t_scene *scene = parse_rt_file(argv[1]);
	if (!scene)
	{
		printf("Error parsing scene file.\n");
		return (1);
	}

	// Here you would typically render the scene or perform further processing
	// For now, we just free the scene
	free_scene(scene);

	return (0);
}
