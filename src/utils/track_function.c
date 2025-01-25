#include "minishell.h"


static void		init_tracking(char **a, char **b, char **c)
{
	*a = NULL;
	*b = NULL;
	*c = NULL;
}

static void 	get_fpath(char *buf, size_t len, const char *name)
{
	
	if (getcwd(buf, len) != NULL)
	{
		ft_strlcat(buf, "/", len - ft_strlen(buf) - 1);
		ft_strlcat(buf, name, len - ft_strlen(buf));
	}
	else
		ft_putstr_fd("fak\n", 1);
}

void 	track_origin(int func)
{
	int 	fd;
	char 	*line;
	char 	*search;
	char 	*found;
	char 	path[128];

	init_tracking(&line, &search, &found);
	get_fpath(path, sizeof(path), "macro.txt");
	printf("%s\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Where is da file ?\n");
		return ;
	}
	search = ft_itoa(func);
	if (!search)
	{
		perror("CONVERSION PROBLEM\n");
		close(fd);
		return ;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strnstr(line, search, ft_strlen(line)))
		{
			found = ft_strdup(line);
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
	if (found)
	{
		ft_putstr_fd(found, 1);
		free(found);
	}
	else
		ft_putstr_fd("No match in tracking\n", 1);
	free(search);
}
