/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:12 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/12 07:08:41 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static bool	pars_get_starter(char *str, char *start)
{
    return (strncmp(str, start, strlen(start)) == 0);
}*/

static char	*extract_word(char *str, int start, int end)
{
	int		i;
	char	*rslt;

	if (!str)
		return (NULL);
	rslt = malloc((end - start) + 1);
	if (!rslt)
		return (NULL);
	i = 0;
	while (start < end)
		rslt[i++] = str[start++];
	rslt[i] = '\0';
	return (rslt);
}

static char	**parse_word_content(t_sh *shell, char *element)
{
	t_utils	u;
	char	**cmd;

	if (!element)
		return (throw_error("NULL element in:", __FILE__, __LINE__), NULL);
	cmd = malloc(3 * sizeof(char *));
	if (!cmd)
		return (free(element),
			throw_error("malloc in:", __FILE__, __LINE__), NULL);
	ft_bzero(&u, sizeof(u));
	while (ft_isalnum(element[u.i]))
		u.i++;
	cmd[0] = extract_word(element, 0, u.i);
	if (!cmd[0])
		return (free(cmd), throw_error("malloc in:", __FILE__, __LINE__), NULL);
	if (ft_isspace(element[u.i]))
		u.i++;
	while (element[u.i + u.j])
		u.j++;
	cmd[1] = extract_word(element, u.i, u.j + u.i);
	debug_arr(shell, (char *[]){"cmd :", cmd[0], "\n", NULL});
	if (!cmd[1])
		return (free(cmd[0]), free(cmd),
			throw_error("malloc in:", __FILE__, __LINE__), NULL);
	cmd[2] = NULL;
	free(element);
	return (cmd);
}

/*
static t_ast	*parse_handle_subscript(char **toks, t_sh *shell)
{
	t_ast	*ast;
	int		len;

	debug(shell, "into hande subscript \n");
	ast = pars_init_ast();
	len = parse_toks_len(toks);
	if (len > 0 && pars_get_starter(toks[0], "("))
	{
		ast->type = AST_SUBSHELL;
		ast->left = parse_handle_script(toks + 1, shell);
		if (pars_get_starter(toks[len - 1], ")"))
			toks[len - 1] = NULL;
    }
    return (ast);
}*/

t_ast	*parse_handle_script(char **toks, t_sh *shell)
{
	t_ast		*ast;
	int			len;
	int			type;
	static int	i = 0;

	len = parse_toks_len(toks);
	ast = pars_init_ast();
	while (i < len)
	{
		i++;
		type = pars_get_type(toks[i - 1]);
		if (type != AST_COMMAND)
		{
			ast->type = pars_get_type(toks[i - 1]);
			ast->op = pars_get_op(toks[i - 1]);
			ast->args = NULL;
			ast->left = parse_handle_script(toks, shell);
			ast->right = parse_handle_script(toks + i, shell);
		}
		else
		{
			ast->type = AST_COMMAND;
			ast->args = parse_word_content(shell, toks[i - 1]);
		}
	}
	return (ast);
}
