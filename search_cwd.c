#include "shell.h"
/**
 * search_cwd - look for current working dir
 *
 * @filename: file name
 * @er: input
 *
 * Return: current working dir
 */
char *search_cwd(char *filename, char *er)
{
	DIR *dir;
	struct dirent *sd;
	char *ret;
	int len = 0;
	int i = 0;

	while (filename[len])
		len++;
	ret = malloc(sizeof(char) * (len + 3));
	dir = opendir(".");
	if (!dir)
	{
		printf("Error! Unable to open directory.\n");
		exit(0);
	}
	while ((sd = readdir(dir)))
	{
		for (i = 0; sd->d_name[i] && filename[i]; i++)
		{
			if (sd->d_name[i] != filename[i])
				break;
			if (i == (len - 1) && !(sd->d_name[i + 1]))
			{
				strcpy(ret, "./");
				strcat(ret, filename);
				closedir(dir);
				if (!(access(ret, X_OK)))
					return (ret);
				write(2, er, 5);
			}
		}
	}
	closedir(dir);
	free(ret);
	return (er);
}
