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

t_ast   *parse_node_redirection(char **toks, t_sh *shell)
{
    t_ast   *node;

    node->args = NULL;
    node->type = AST_OP_NULL;
    node->left = parse_commands(toks, shell);
    if (ft_strncmp(*toks, ">>", ft_strlen(*toks)))
        node->type = AST_OP_DGREAT;
    else if (ft_strncmp(*toks, ">", ft_strlen(*toks)))
        node->type = AST_OP_GREAT;
    else if (ft_strncmp(*toks, "<<", ft_strlen(*toks)))
        node->type = AST_OP_DLESS;
    else if (ft_strncmp(*toks, "<", ft_strlen(*toks)))
        node->type = AST_OP_LESS;
    toks++;
    node->right = parse_commands(toks, shell);
    return (node);
}

t_ast   *parse_node_commands(char **tokens, t_sh *shell)
{
    t_ast	*node;
    char    *word;
    int     current_type;

	node->type = AST_COMMAND;
    ft_memmove(word, *tokens, (size_t)ft_strlen(tokens));
    current_type = pars_get_type(*tokens);
	while (current_type == AST_COMMAND)
    {
        word = ft_strjoin(word, *tokens);
        tokens++;
        current_type = pars_get_type(*tokens);
    }
    ft_memmove(node->args, word, (size_t)ft_strlen(word));
    shell->ast.log++;
    node->left = NULL;
    node->right = NULL;
	return (node);
}

t_ast	*parse_node_pipeline(char **tokens, t_sh *shell)
{
    t_ast   *node;

    debug(shell, "Entering node pipe \n");
    debug(shell, *tokens);
    node = NULL;
    return (node);
}

t_ast   *parse_node_logical(char **tokens, t_sh *shell)
{
    t_ast   *node;

    debuf(shell, "Entering node logical \n");
    debug(shell, *tokens);
    node = NULL;
    return (node);
}
