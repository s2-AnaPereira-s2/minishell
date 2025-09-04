/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:42:57 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/04 19:26:39 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s\n", (char *)lst->content);
        lst = lst->next;
    }
}*/

void tokenizing(t_token *token)
{
    t_list *temp;

    temp = token->lexemes;
    while (temp)
    {
        if (ft_strncmp((char *)temp->content, "|", 1) == 0)
            ft_lstadd_back(&token->TOKEN_PIPE, ft_lstnew(temp->content));
        else if (ft_strncmp((char *)temp->content, ">>", 2) == 0)
            ft_lstadd_back(&token->TOKEN_APPEND, ft_lstnew(temp->content));
        else if (ft_strncmp((char *)temp->content, "<<", 2) == 0)
            ft_lstadd_back(&token->TOKEN_HEREDOC, ft_lstnew(temp->content));
        else if (ft_strncmp((char *)temp->content, "<", 1) == 0)
            ft_lstadd_back(&token->TOKEN_REDIR_IN, ft_lstnew(temp->content));
        else if (ft_strncmp((char *)temp->content, ">", 1) == 0)
            ft_lstadd_back(&token->TOKEN_REDIR_OUT, ft_lstnew(temp->content));
        else
            ft_lstadd_back(&token->TOKEN_WORD, ft_lstnew(temp->content));
        temp = temp->next;
    }
}


void get_lexemes(t_token *token, char *input)
{
    int i;
    int start;

    start = 0;
    i = 0;
    token->lexemes = NULL;
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        start = i;
        if (input[i] == '"' || input[i] == '\'')
        {
            char quote = input[i++];
            start = i;
            while (input[i] && input[i] != quote)
                i++;
            if (i > start)
                ft_lstadd_back(&token->lexemes, ft_lstnew(ft_substr(input, start, i - start)));
            if (input[i] == quote)
                i++; 
        }
        else 
        {
            while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'')
                i++;
            if (i > start)
                ft_lstadd_back(&token->lexemes, ft_lstnew(ft_substr(input, start, i - start)));
        }
    }
    tokenizing(token);
} 

void token_init(t_token *token, char *input)
{
    token->lexemes = NULL;
    token->TOKEN_WORD = NULL;
    token->TOKEN_PIPE = NULL;
    token->TOKEN_REDIR_IN = NULL;
    token->TOKEN_REDIR_OUT = NULL;
    token->TOKEN_APPEND = NULL;
    token->TOKEN_HEREDOC = NULL;
    get_lexemes(token, input);
}
