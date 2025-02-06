#include "minishell.h"

t_ast   parse_node_ast(t_atype type, t_aop op, t_ast *left, t_ast *right)
{
    t_ast   node;

    node.type = type;
    node.op = op;
    node.left = left;
    node.right = right;
    node.args = NULL;
    return (node);
}

t_ast   parse_redirection(char **toks, t_sh *shell)
{
    t_aop   op;
    t_ast   left;
    t_ast   right;

    op = AST_OP_NULL;
    left = parse_commands(toks, shell);
    if (ft_strncmp(*toks, ">>", ft_strlen(*toks)))
        op = AST_OP_DGREAT;
    else if (ft_strncmp(*toks, ">", ft_strlen(*toks)))
        op = AST_OP_GREAT;
    else if (ft_strncmp(*toks, "<<", ft_strlen(*toks)))
        op = AST_OP_DLESS;
    else if (ft_strncmp(*toks, "<", ft_strlen(*toks)))
        op = AST_OP_LESS;
    toks++;
    right = parse_commands(toks, shell);
    return (parse_node_ast(AST_REDIRECT, op, &left, &right));
}

t_ast   parse_commands(char **tokens, t_sh *shell)
{
    t_ast	node;
	
	node.type = AST_COMMAND;
	node.args = parse_collector(tokens, shell);
	return (node);
}

t_ast	parse_pipeline(char **tokens, t_sh *shell)
{
	t_ast	left;
	t_ast	right;
	t_ast	origin;

	left = parse_logical(tokens, shell);
	origin = left;
	while (*tokens && ft_strncmp(*tokens, "|", ft_strlen(*tokens)))
	{
		tokens++;
		right = parse_logical(tokens, shell);
		origin = parse_node_ast(AST_PIPELINE, AST_OP_NULL, &left, &right);
		left = origin;
	}
	return (origin);
}

t_ast   parse_logical(char **tokens, t_sh *shell)
{
	t_aop	op;
    t_ast	left;
    t_ast   right;
    t_ast   origin;

    left = parse_commands(tokens, shell);
    origin = left;
    while (*tokens && check_gates(tokens))
	{
		op = AST_OP_NULL;
		if (!ft_strncmp(*tokens, "&&", ft_strlen(*tokens)))
			op = AST_OP_AND;
		else if (!ft_strncmp(*tokens, "||", ft_strlen(*tokens)))
			op = AST_OP_OR;
		tokens++;
		right = parse_commands(tokens, shell);
		origin = parse_node_ast(AST_LOGICAL, op, &left, &right);
	}
	return (origin);
}
