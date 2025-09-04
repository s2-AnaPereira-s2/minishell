/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:04:06 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/09/04 19:25:41 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"


typedef struct s_token
{
    t_list *lexemes;
    t_list *TOKEN_WORD;
    t_list *TOKEN_PIPE;
    t_list *TOKEN_REDIR_IN;
    t_list *TOKEN_REDIR_OUT;
    t_list *TOKEN_APPEND;
    t_list *TOKEN_HEREDOC;
    
} t_token;

void token_init(t_token *token, char *input);

#endif