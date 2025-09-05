/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:09 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/05 17:20:06 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_tokens(t_tokens **tokens, t_cmd **cmd)
{
	t_list	*new;
	t_tokens	*temp;
	t_cmd	**current_cmd;
	
    if (!tokens || !*tokens || !cmd)
        return;
    
    temp = *tokens;
    current_cmd = *cmd;

    while (temp)
    {
        if (temp->type == TOKEN_WORD)
        {
            new = ft_lstnew(temp->value);
            if (!new)
                return ;
            ft_lstadd_back(&((*current_cmd)->args), new);
        }
        else if (temp->type == TOKEN_REDIR_IN)
        {
            if (temp->next)
            {
                (*current_cmd)->redir_in = ft_strdup(temp->next->value);
                temp = temp->next;
            }
            else
            {
                printf("Error: Missing filename after '<'\n");
                break;
            }
        }
        else if (temp->type == TOKEN_REDIR_OUT)
        {
            if (temp->next)
            {
                (*current_cmd)->redir_out = ft_strdup(temp->next->value);
                temp = temp->next;
            }
            else
            {
                printf("Error: Missing filename after '>'\n");
                break;
            }
        }
        else if (temp->type == TOKEN_APPEND)
        {
            if (temp->next)
            {
                (*current_cmd)->append = ft_strdup(temp->next->value);
                temp = temp->next;
            }
            else
            {
                printf("Error: Missing filename after '>>'\n");
                break;
            }
        }
        else if (temp->type == TOKEN_HEREDOC)
        {
            if (temp->next)
            {
                (*current_cmd)->heredoc = ft_strdup(temp->next->value);
                temp = temp->next;
            }
            else
            {
                printf("Error: Missing delimiter after '<<'\n");
                break;
            }
        }
        else if (temp->type == TOKEN_PIPE)
        {
            (*current_cmd)->next = malloc(sizeof(t_cmd));
            if (!(*current_cmd)->next)
                return ;
            cmd_init((*current_cmd)->next);
            current_cmd = &((*current_cmd)->next);
        }
        temp = temp->next;
    }
    while (*cmd)
    {
        t_list *arg = (*cmd)->args;
        printf("Command arguments:\n");
        while (arg)
        {
            printf(" - %s\n", (char *)arg->content);
            arg = arg->next;
        }
        if ((*cmd)->redir_in)
            printf("Input redirection: %s\n", (*cmd)->redir_in);
        if ((*cmd)->redir_out)
            printf("Output redirection: %s\n", (*cmd)->redir_out);
        if ((*cmd)->append)
            printf("Append redirection: %s\n", (*cmd)->append);
        if ((*cmd)->heredoc)
            printf("Heredoc: %s\n", (*cmd)->heredoc);
        cmd = &((*cmd)->next);
    }
}
