#include "pipex.h"


char *get_path(char **env)
{
	int i = 0;
	char *t;

	while (env[i])
	{
		t = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
		if (NULL != t)
		{
			while(*t != '/')
				t++;
			return (ft_strdup(t));
		}
		i++;
	}
	return NULL;
}

char	*ft_append(char *left, char  * right)
{
	char	*target;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	target = (char *)malloc(ft_strlen(left) + ft_strlen(right) + 1);
	if (!target)
		return NULL;
	while (left[i] || right[j])
	{
		if (left[i])
			target[k++] = left[i++];
		else
			target[k++] = right[j++];
	}
	target[k] = '\0';
	free(left);
	return target;
}


char **__slice(char *path)
{
	char **arr = ft_split(path, ':');
	free(path);
	return arr;
}


void mah()
{
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}

char *current_lookup(char *cmd, char *path)
{
	path = ft_strdup(path);
	path = ft_append(path, "/");
	path = ft_append(path, cmd);

	// printf("%s\n", path);

	if (0 == access(path, F_OK))
		return path;

	free(path);
	return (NULL);
}

char *cmd_lookup(char *cmd, char **newenv)
{

	int i = 0;
	char * current = NULL;
	while (newenv[i])
	{
		current = current_lookup(cmd, newenv[i]);
		if (0 != current)
			break;
		i++;
	}

	return current;
}

int cmd_handle(char *cmd, char **env)
{
	char ** arr = __slice(get_path(env));

	for (int i = 0; arr[i]; i++)
	{
		printf("%s\n", arr[i]);
	}
	ft_free_split(arr);
	return 0;
}
