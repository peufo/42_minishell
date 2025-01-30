#include "minishell.h"

static void	select_string(char *s)
{
	get_macro(s);
}

void	init_tracking(char **a, char **b, char **c)
{
	*a = NULL;
	*b = NULL;
	*c = NULL;
}

void	get_fpath(char *buf, size_t len)
{
	if (getcwd(buf, len) != NULL)
	{
		ft_strlcat(buf, "/", len - ft_strlen(buf) - 1);
		ft_strlcat(buf, "src/utils/macro.txt", len - ft_strlen(buf));
	}
	else
		ft_putstr_fd("fak\n", 1);
}

static void	looking(int fd, char **line, char **search, char **found)
{
	*line = get_next_line(fd);
	while (*line != NULL)
	{
		if (ft_strnstr(*line, *search, ft_strlen(*line)))
		{
			*found = ft_strdup(*line);
			free(*line);
			break ;
		}
		free(*line);
		*line = get_next_line(fd);
	}
	close(fd);
	if (*found)
	{
		select_string(*found);
		free(*found);
	}
	else
		ft_putstr_fd("No match in tracking\n", 1);
	free(*search);
}

void	track_origin(int func)
{
	int		fd;
	char	*line;
	char	*search;
	char	*found;
	char	path[256];

	init_tracking(&line, &search, &found);
	get_fpath(path, sizeof(path) + 2);
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
	looking(fd, &line, &search, &found);
}
