#include "minishell.h"

void 	track_origin(int func)
{
	int 	fd;
	char 	*line;
	char 	*search;
	char 	*found;

	printf("AAAAAAAAAAAAAAAAAAA\n");
	fd = open("macro.txt", O_RDONLY);
	if (fd < 0)
		return ;
	search = ft_itoa(func);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strnstr(line, search, 80))
			found = ft_strdup(line);
		free(line);
		break ;
	}
	free(line);
	close(fd);
	ft_putstr_fd(found, 1);
	free(found);
	free(search);
}
