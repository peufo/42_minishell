/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_geters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:05 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/10 10:40:00 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_atype	pars_get_type(char *tok)
{
	int				i;
	static t_ttype	ttype[] = {
	{"&&", AST_LOGICAL},
	{"||", AST_LOGICAL},
	{"|", AST_PIPELINE},
	{"(", AST_SUBSHELL},
	{"<", AST_REDIRECT},
	{">", AST_REDIRECT},
	{">>", AST_REDIRECT},
	{"<<", AST_REDIRECT},
	{NULL, 0}
	};

	i = 0;
	if (tok == NULL)
		return (AST_END);
	while (ttype[i].tok)
	{
		if (!ft_strcmp(ttype[i].tok, tok))
			return (ttype[i].op);
		i++;
	}
	return (AST_COMMAND);
}

t_aop	pars_get_op(char *tok)
{
	int				i;
	static t_otype	otype[] = {
	{"&&", AST_OP_AND},
	{"||", AST_OP_OR},
	{"<", AST_OP_LESS},
	{">", AST_OP_GREAT},
	{">>", AST_OP_DGREAT},
	{"<<", AST_OP_DLESS},
	{NULL, 0}
	};

	i = 0;
	while (otype[i].tok)
	{
		if (!ft_strcmp(otype[i].tok, tok))
			return (otype[i].op);
		i++;
	}
	return (AST_OP_NULL);
}

int	parse_toks_len(char **toks)
{
	int	size;

	size = 0;
	while (toks[size])
		size++;
	return (size);
}

int	parse_get_nbops(char **toks, int len)
{
	int	n;

	n = 0;
	while (len > 0)
		if (pars_get_type(toks[--len]) != AST_COMMAND)
			n++;
	return (n);
}

t_list	*pars_get_typelist(char **toks, int mod, t_sh *shell)
{
	t_list	*lst;
	int		type;
	int		i;

	i = 0;
	lst = NULL;
	type = pars_get_type(toks[i]);
	while (toks[i] && type != AST_END)
	{
		if (mod == AST_COMMAND)
		{
			if (type == mod)
				ft_lstadd_back(&lst, ft_lstnew(toks[i]));
		}
		else
		{
			if (type != AST_COMMAND)
				ft_lstadd_back(&lst, ft_lstnew(toks[i]));
		}
		type = pars_get_type(toks[++i]);
	}
	debug_two_lists(shell, NULL, lst);
	return (lst);
}
