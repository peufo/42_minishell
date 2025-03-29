
#include "minishell.h"

void	exec_redir_save_std(t_ast *node)
{
	t_redir	*rh;

	if (node->is_child_process)
		return ;
	rh = &node->redir;
	if (rh->files_out || rh->files_out_append)
	{
		rh->fd_std_out = dup(STDOUT_FILENO);
		if (rh->fd_std_out == -1)
			shell_exit(node->shell);
	}
	if (rh->files_in)
	{
		rh->fd_std_in = dup(STDIN_FILENO);
		if (rh->fd_std_in == -1)
			shell_exit(node->shell);
	}
}

void	exec_redir_restore_std(t_ast *node)
{
	t_redir *rh;

	rh = &node->redir;
	if (rh->fd_std_out && (rh->files_out || rh->files_out_append))
	{
		dup2(rh->fd_std_out, STDOUT_FILENO);
		close(rh->fd_std_out);
	}
	if (rh->fd_std_in && rh->files_in)
	{
		dup2(rh->fd_std_in, STDIN_FILENO);
		close(rh->fd_std_in);
	}
}