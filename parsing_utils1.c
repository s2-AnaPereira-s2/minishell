/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:48:22 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/05 17:18:18 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    cmd_init(t_cmd **cmd)
{
    *cmd = malloc(sizeof(t_cmd));
    if (!*cmd)
        return;
    (*cmd)->args = NULL;
    (*cmd)->redir_in = NULL;
    (*cmd)->redir_out = NULL;
    (*cmd)->append = NULL;
    (*cmd)->heredoc = NULL;
    (*cmd)->next = NULL;
}

char **args_array(t_list *args)
{
    int len;
    char **args_array;
    t_list *temp;
    int i;

    len = ft_lstsize(args);
    args_array = malloc((len + 1) * sizeof(char *));
    temp = args;
    i = 0;
    if (!args)
        return NULL;
    while (temp)
    {
        args_array[i++] = ft_strdup(temp->content);
        temp = temp->next;
    }
    args_array[i] = NULL;
    return (args_array);
}