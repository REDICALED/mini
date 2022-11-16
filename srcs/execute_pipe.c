#include "minishell.h"

static void	dup_child(t_global *global, int idx, int *fd)
{
	t_p_mom	*p_mom;

	p_mom = &(global->p_arr[idx]);
	if (p_mom->head->token == e_pipe)
	{
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	if (p_mom->input != -1)
		dup2(p_mom->input, STDIN_FILENO);
	if (p_mom->output != -1)
		dup2(p_mom->output, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

static int	pipe_run(t_global *global, int idx)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup_child(global, idx, fd);
		run_cmd(global, idx);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (pid);
}

static int	last_pipe_run(t_global *global, int idx)
{
	pid_t	pid;
	t_p_mom	*p_mom;

	p_mom = &(global->p_arr[idx]);
	pid = fork();
	if (pid == 0)
	{
		if (p_mom->input != -1)
			dup2(p_mom->input, STDIN_FILENO);
		if (p_mom->output != -1)
			dup2(p_mom->output, STDOUT_FILENO);
		run_cmd(global, idx);
	}
	return (pid);
}

void	execute_pipe(t_global *global)
{
	int		i;
	pid_t	pid_li[global->p_count + 1];
	int		status;

    i = 0;
	while (i < global->p_count && global->p_arr[i].head)
	{
		if (global->p_arr[i].head && global->p_arr[i].head->token != e_pipe)
			pid_li[i] = pipe_run(global, i);
		else if ((global->p_arr[i].head && global->p_arr[i].head->token \
				== e_pipe) || global->p_arr[i].head == NULL)
			exit(global->p_arr[i].read_error);
		i++;
	}
	pid_li[i] = last_pipe_run(global, i);
	i = 0;
	while (i <= global->p_count && global->p_arr[i].head)
	{
		waitpid(pid_li[i], &status, 0);
		if (i == global->p_count)
			g_exit_code = WEXITSTATUS(status);
		i++;
	}
}