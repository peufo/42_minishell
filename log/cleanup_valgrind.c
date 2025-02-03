#include "minishell.h"

static void	messages(int error)
{
	if (error == 0)
		ft_putstr("nfd wasn't created\n");
	if (error == 1)
		ft_putstr("Leaks.log were cleaned !\n");
	else
		ft_putstr("Unknown error\n");
}

static void	get_pass_it(int fd, int nfd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && ft_strlen(line) > 11)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}

static void	get_relevant_info(int fd, int nfd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strnstr(line, "readline", ft_strlen(line)))
			get_pass_it(fd, nfd);
		else
			ft_putstr_fd(line, nfd);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}

int	main()
{
	int	fd;
	int	nfd;

	fd = open("leaks.log", O_RDONLY, 0666);
	if (!fd)
		return (0);
	nfd = open("clean_leaks.log", O_CREAT | O_WRONLY, 0666);
	if (!nfd)
		return (close(fd), messages(0), 0);
	get_relevant_info(fd, nfd);
	close(fd);
	close(nfd);
	return (message(1), 1);
}