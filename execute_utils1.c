/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:13:52 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/12 18:58:16 by ana-pdos         ###   ########.fr       */
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
        return ;
    i = 0;
    while (i < data->cmds - 1)
    {
        if (pipe(&data->pipefds[i * 2]) < 0)
        {
            perror("pipe failed");
            return;
        }
        i++;
    }
}

void    process_pids(t_data *data, t_cmd **cmd)
{
    int i;
    
    data->pids = malloc(sizeof(pid_t) * data->cmds);
    if (!data->pids)
        return ;
    if (data->cmds == 1)
    {
        data->pids[0] = fork();
        if (data->pids[0] < 0)
        {
            perror("Fork failed");
            return ;
        }
        if (data->pids[0] == 0)
        {
            execute_one_cmd(cmd, data);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        waitpid(data->pids[0], NULL, 0);
        return ;
    }
    else
    {
        i = 0;
        while(i < data->cmds)
        {
            data->pids[i] = fork();
            if (data->pids[i] < 0)
            {
                perror("Fork failed");
                return ;
            }
            if (data->pids[i] == 0)
            {
                printf("I'm here executing command\n");
                execute_basic_cmds(cmd, data, i);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
            i++;
        }
        i = 0;
        while (i < data->cmds)
        {
            waitpid(data->pids[i], NULL, 0);
            i++;
        }    
    }
}






















/*
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
    
    temp = *cmd;
    data->pipefds = malloc(sizeof(int) * (2 * (data->cmds - 1)));
    if (!data->pipefds)
        return ;   
    process_pids(data, temp->args);
}

void    process_pids(t_data *data, t_list *args)
{
    int i;
    
    data->pids = malloc(sizeof(pid_t) * data->cmds);
    if (!data->pids)
        return ;
    if (data->cmds == 1)
    {
        data->pids[0] = fork();
        if (data->pids[0] < 0)
        {
            perror("Fork failed");
            return ;
        }
        if (data->pids[0] == 0)
        {
            execute_one_cmd(data, args);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        waitpid(data->pids[0], NULL, 0);
        return ;
    }
    else
    {
        i = 0;
        while(i < data->cmds)
        {
            data->pids[i] = fork();
            if (data->pids[i] < 0)
            {
                perror("Fork failed");
                return ;
            }
            if (data->pids[i] == 0)
            {
                execute_basic_cmds(data, args, i);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
            i++;
        }
        i = 0;
        while (i < data->cmds)
        {
            waitpid(data->pids[i], NULL, 0);
            i++;
        }
            
    }
}
*/






















/*
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

void    get_pipefds(t_data *data)
{
    int i;
    
    data->pipefds = malloc(sizeof(int) * (2 * (data->cmds - 1)));
    if (!data->pipefds)
        return ;
    i = 0;
    while (i < data->cmds - 1)
    {
        if (pipe(&data->pipefds[i * 2]) < 0)
        {
            perror("pipe failed");
            return ;
        }
        i++;
    }
}

void    process_pids(t_data *data, t_list *args)
{
    int i;
    
    data->pids = malloc(sizeof(pid_t) * data->cmds);
    if (!data->pids)
        return ;
    if (data->cmds == 1)
    {
        data->pids[0] = fork();
        if (data->pids[0] < 0)
        {
            perror("Fork failed");
            return ;
        }
        if (data->pids[0] == 0)
        {
            printf("Command path: %s\n", data->cmd_paths[0]);
            execute_one_cmd(data, args);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        waitpid(data->pids[0], NULL, 0);
        return ;
    }
    else
    {
        i = 0;
        while(i < data->cmds)
        {
            data->pids[i] = fork();
            if (data->pids[i] < 0)
            {
                perror("Fork failed");
                return ;
            }
            if (data->pids[i] == 0)
            {
                execute_basic_cmds(data, args, i);
                perror("execve failed");
                exit(EXIT_FAILURE);  
            }
            i++;
        }
        
        // Close all pipe file descriptors in parent
        i = 0;
        while (i < 2 * (data->cmds - 1))
        {
            close(data->pipefds[i]);
            i++;
        }
        
        // Wait for all children
        i = 0;
        while (i < data->cmds)
        {
            waitpid(data->pids[i], NULL, 0);
            i++;
        }
    }
}*/
