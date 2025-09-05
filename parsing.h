/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:04:06 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/09/05 17:33:27 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC
}   t_token_type;

typedef struct s_tokens
{
    t_token_type    type;
    char            *value;
    struct s_tokens  *next;
}   t_tokens;

typedef struct s_cmd
{
    t_list        *args;      
    char        *redir_in;   
    char        *redir_out;  
    char        *append;     
    char        *heredoc;    
    struct s_cmd *next;  
} t_cmd;

typedef struct s_data
{
    char        **envp;
} t_data;


void get_lexemes(t_list **lexemes, t_tokens **tokens, char *input);
void	parse_tokens(t_tokens **tokens, t_cmd **cmd);
void    cmd_init(t_cmd **cmd);
void cleaning_func(t_tokens **tokens, t_list **lexemes, t_cmd **cmd);

#endif