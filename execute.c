/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:44:12 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/08 14:44:44 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	execute_first(t_data *data)
{
	dup2(pipex->infile_fd, 0);
	dup2(pipex->pipefd[1], 1);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	execve(pipex->cmd_path1, pipex->cmd1, pipex->p_envp);
	ft_printf("%s\n", "error execve 1");
	free_array(pipex->paths);
	free(pipex->cmd_path1);
	exit(1);
}