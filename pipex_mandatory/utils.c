/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:06:07 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/02/14 17:06:29 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>


void	ft_error(char *msg)
{
	perror(msg);
	exit(1);
}

int	ft_return(char *msg, int r)
{
	perror(msg);
	return r;
}

void execute_child_process(char *command, char **envp, int *pipe_fd, int child_num)
{
    if (child_num == 1)
    {
        close(pipe_fd[0]);
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_error("dup2");
        close(pipe_fd[1]);
    }
    else if (child_num == 2)
    {
        close(pipe_fd[1]);
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			ft_error("dup2");
        close(pipe_fd[0]);
    }
    execute_command(command, envp);
}

int create_pipe_and_forks(char **av, char **envp)
{
    int pipe_fd[2];
    pid_t child1, child2;

    if (pipe(pipe_fd) == -1)
		ft_return("pipe", -1);
    child1 = fork();
    if (child1 == -1)
		ft_return("fork", -1);
    if (child1 == 0)
    {
		if (ft_open_input_fd(av))
			exit(1);
        execute_child_process(av[2], envp, pipe_fd, 1);
    }
    child2 = fork();
    if (child2 == -1)
		ft_return("fork", -1);
    if (child2 == 0)
        execute_child_process(av[3], envp, pipe_fd, 2);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);
    return 0;
}

void handle_pip_processes(char **av, char **envp)
{
    if (create_pipe_and_forks(av, envp) == -1)
		ft_error("Error creating pip and forcking");
}
