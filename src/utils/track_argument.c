#include "minishell.h"

static void	type_or_func(char **s)
{
	int		i;
	int		j;
	int		int_num;
	char	number[256];

	i = 0;
	j = 0;
	if (!*s)
		return ;
	(void)int_num;
	(void)number;
	(void)i;
	(void)j;
//	while (*s[i])
//	{
//		if (!ft_isdigit(*s[i]))
//			number[j++] = *s[i];
//		i++;
//	}
//	number[j] = '\0';
//	int_num = ft_atoi(number);
//	if (int_num >= 100 && int_num <= 200)
//		ft_putstr_fd("Argument type : ", 1);
}

void	get_macro(char *s)
{
	int	i;

	i = 0;
	type_or_func(&s);
	while (s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			ft_putchar_fd(s[i++], 1);
		else
			i++;
	}
	ft_putchar_fd('\n', 1);
}
