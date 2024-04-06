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

int iscmd(char *cmd, char **newenv)
{
	char *ret = cmd_lookup(cmd, newenv);

	free(ret);

	return (NULL != ret);
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


void esh(char **arr)
{
	if (!arr)
	{
		printf("null array\n");
		return ;
	}
	for (int i = 0; arr[i]; i++)
	{
		printf("%s\n", arr[i]);
	}
}


t_cmds cmd_handle(char **av, char **newenv)
{
	t_cmds res;

	res.left = ft_split(av[2], ' ');
	res.right = ft_split(av[3], ' ');

	char *c1 = cmd_lookup(res.left[0], newenv);
	char *c2 = cmd_lookup(res.right[0], newenv);


	if (!c1 || !c2)
	{
		ft_free_split(res.left);
		ft_free_split(res.right);
		mah();
	}

	free(res.left[0]);
	res.left[0] = c1;
	free(res.right[0]);
	res.right[0] = c2;
	return res;
}
