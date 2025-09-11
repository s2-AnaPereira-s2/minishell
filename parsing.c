/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:09 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/11 15:19:16 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_tokens(t_tokens **tokens, t_cmd **cmd)
{
	t_list	*new;
	t_tokens	*temp;
	t_cmd	*current_cmd;
	
    if (!tokens || !*tokens || !cmd)
        return;
    temp = *tokens;
    current_cmd = *cmd;
    while (temp)
    {
        if (temp->type == TOKEN_WORD)
        {
            new = ft_lstnew(ft_strdup(temp->value));
            if (!new)
                return ;
            ft_lstadd_back(&((current_cmd)->args), new);
        }
        else if (temp->type == TOKEN_REDIR_IN)
        {
            if (!temp->next || temp->next->type != TOKEN_WORD)
            {
                printf("Error: Missing filename after '<'\n");
                return ;
            }
            (current_cmd)->redir_in_file = ft_strdup(temp->next->value);
            temp = temp->next;
        }
        else if (temp->type == TOKEN_REDIR_OUT)
        {
            if (!temp->next || temp->next->type != TOKEN_WORD)
            {
                printf("Error: Missing filename after '>'\n");
                return ;
            }
            (current_cmd)->redir_out_file = ft_strdup(temp->next->value);
            temp = temp->next;
        }
        else if (temp->type == TOKEN_APPEND)
        {
            if (!temp->next || temp->next->type != TOKEN_WORD)
            {
                printf("Error: Missing filename after '>>'\n");
                return ;
            }
            (current_cmd)->append_file = ft_strdup(temp->next->value);
            temp = temp->next;
        }
        else if (temp->type == TOKEN_HEREDOC)
        {
            if (!temp->next || temp->next->type != TOKEN_WORD)
            {
                printf("Error: Missing delimiter after '<<'\n");
                return ;
            }
            (current_cmd)->heredoc_limiter = ft_strdup(temp->next->value);
            temp = temp->next;
        }
        else if (temp->type == TOKEN_PIPE)
        {
            if (!temp->next)
            {
                printf("Error: Missing command and argument after '|'\n");
                return ;
            }
            cmd_init(&(current_cmd->next));
            current_cmd = current_cmd->next;
        }
        temp = temp->next;
    }
    /*
    // Debug print
    t_cmd *c = *cmd;
    while (c)
    {
        t_list *arg = c->args;
        printf("Command arguments:\n");
        while (arg)
        {
            printf(" - %s\n", (char *)arg->content);
            arg = arg->next;
        }
        if (c->redir_in_file)
            printf("Input redirection: %s\n", c->redir_in_file);
        if (c->redir_out_file)
            printf("Output redirection: %s\n", c->redir_out_file);
        if (c->append_file)
            printf("Append redirection: %s\n", c->append_file);
        if (c->heredoc_limiter)
            printf("Heredoc: %s\n", c->heredoc_limiter);
        c = c->next;
    }
    */
    
}


