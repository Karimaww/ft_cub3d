#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// Comparison function for sorting
int	compare(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}
/**
 * @brief Function that gets all the file names from the designated directory
 * 
 * @param cub dir_name
 * @return int 
 */
// int	iter_dir(t_cub *cub, t_sprite *sprite, char *dir_name)
// {
// 	DIR	*directory;
// 	struct dirent *entry;
// 	char *file_names[1000]; // Assuming a maximum of 1000 files, adjust as needed

// 	sprite->files_size = 0;
// 	directory = opendir(dir_name);
// 	if (directory == NULL)
// 		return (perror("opendir"), 1);

// 	// Loop through each file in the directory and store their names
// 	while ((entry = readdir(directory)) != NULL)
// 	{
// 		if (entry->d_type == DT_REG)
// 		{ // Check if it's a regular file
// 			file_names[sprite->files_size] = strdup(entry->d_name);
// 			sprite->files_size++;
// 		}
// 	}
// 	closedir(directory);
// 	qsort(file_names, sprite->files_size, sizeof(char *), compare);
// 	for (int i = 0; i < sprite->files_size; i++)
// 	{
// 		printf("File name: %s\n", file_names[i]);
// 		free(file_names[i]); // Free the memory allocated by strdup
// 	}
// 	return 0;
// }