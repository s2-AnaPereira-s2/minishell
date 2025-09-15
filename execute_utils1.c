/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:13:52 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/15 19:15:11 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void get_cmds_count(t_cmd **cmd, t_data *data)
{
   t_cmd *temp;

   temp = *cmd;
   data->cmds = 0;
   while (temp)
   {
       data->cmds += 1;
       temp = temp->next;
   }
}

void    get_pipefds(t_cmd **cmd, t_data *data)
{
    t_cmd *temp;
    int i;
    
    temp = *cmd;
    data->pipefds = malloc(sizeof(int) * (2 * (data->cmds - 1)));
    if (!data->pipefds)
    {
        return ;
    }
    i = 0;
    while (i < data->cmds - 1)
    {
        if (pipe(&data->pipefds[i * 2]) < 0)
        {
            perror("pipe failed");
            free(data->pipefds);
            return;
        }
        i++;
    }
}

void process_one_cmd(t_cmd **cmd, t_data *data)
{
    data->pids[0] = fork();
    if (data->pids[0] < 0)
    {
        perror("Fork failed");
        free(data->pids);
        return ;
    }
    if (data->pids[0] == 0)
    {
        execute_one_cmd(cmd, data);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
    waitpid(data->pids[0], NULL, 0);
}

void process_cmds(t_cmd **cmd, t_data *data)
{
    int i;
    
    i = 0;
    while(i < data->cmds)
    {
        data->pids[i] = fork();
        if (data->pids[i] < 0)
        {
            perror("Fork failed");
            free(data->pids);
            return ;
        }
        if (data->pids[i] == 0)
        {
            execute_basic_cmds(cmd, data, i);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    i = 0;
    while(i < 2 * (data->cmds - 1))
        close(data->pipefds[i++]);
    i = 0;
    while (i < data->cmds)
        waitpid(data->pids[i++], NULL, 0);  
}

void    process_pids(t_data *data, t_cmd **cmd)
{
    data->pids = malloc(sizeof(pid_t) * data->cmds);
    if (!data->pids)
        return ;
    if (data->cmds == 1)
    {
        process_one_cmd(cmd, data);
        return ;
    }
    else
        process_cmds(cmd, data);
}
