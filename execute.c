/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:44:12 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/11 20:13:11 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	execute_one_cmd(t_data *data, t_list *args)
{
    char **aa;

    aa = args_array(args);
	execve(data->cmd_paths[0], aa, data->envp);
    free_array(aa);
}

void    execute_basic_cmds(t_data *data, t_list *args, int cmd_index)
{
    char **aa;
    int i;

    aa = args_array(args);
    if (cmd_index == 0)
    {
        dup2(data->pipefds[1], 1);
    }
    else if (cmd_index == data->cmds - 1)
    {
        dup2(data->pipefds[2 * (cmd_index - 1)], 0);
    }
    else
    {
        dup2(data->pipefds[2 * (cmd_index - 1)], 0);
        dup2(data->pipefds[2 * (cmd_index + 1)], 1);
    }
    i = 0;
    while (i < cmd_index * 2)
    {
        close(data->pipefds[i]);
        i++;
    }
    
    execve(data->cmd_paths[cmd_index], aa, data->envp);
    perror("execve failed");
    free_array(aa);
    exit(EXIT_FAILURE);
}