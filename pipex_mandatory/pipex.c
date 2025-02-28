/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:07:20 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/02/14 17:07:49 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	ft_open_input_fd(char **av)
{
	int	input_fd;

	input_fd = open(av[1], O_RDONLY);
	if (input_fd == -1)
	{
		perror("open input_file");
		return (1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 input_file");
		close(input_fd);
		return (1);
	}
	close(input_fd);
	return (0);
}

int	ft_open_output_fd(int ac, char **av)
{
	int	output_fd;

	output_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_fd == -1)
	{
		perror("open output_file");
		return (1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output_file");
		close(output_fd);
		return (1);
	}
	close(output_fd);
	return (0);
}

int main(int ac, char **av, char **envp)
{
    if (ac < 5)
    {
        fprintf(stderr, "Usage: %s <input_file> <cmd1> <cmd2> ... <cmdN> <output_file>\n", av[0]);
        exit(1);
    }

    if (ft_open_output_fd(ac, av))
        exit(1);
    handle_pip_processes(av, envp);
    return 0;
}
