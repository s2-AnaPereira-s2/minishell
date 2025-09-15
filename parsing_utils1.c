/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:48:22 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/15 19:09:00 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    cmd_init(t_cmd **cmd)
{
    *cmd = malloc(sizeof(t_cmd));
    if (!*cmd)
        return;
    (*cmd)->args = NULL;
    (*cmd)->redir_in_file = NULL;
    (*cmd)->redir_out_file = NULL;
    (*cmd)->append_file = NULL;
    (*cmd)->heredoc_limiter = NULL;
    (*cmd)->next = NULL;
}

char **args_to_array(t_cmd **cmd)
{
    t_list *temp;
    int len;
    int i;
    
    i = 0;  
    len = ft_lstsize((*cmd)->args);
    (*cmd)->args_array = malloc((len + 1) * sizeof(char *));
    if (!(*cmd)->args_array)
        return (NULL);
    temp = (*cmd)->args;
    if (!temp)
        return (NULL);
    while (temp)
    {
        (*cmd)->args_array[i++] = ft_strdup(temp->content);  
        temp = temp->next;
    }
    (*cmd)->args_array[i] = NULL; 
    return ((*cmd)->args_array);
}

