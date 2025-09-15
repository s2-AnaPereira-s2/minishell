/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:04:06 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/09/15 15:06:34 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <sys/wait.h>
#include <fcntl.h>

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
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
    char        **args_array;
    int         index_args_array;
    char        *redir_in_file;   
    char        *redir_out_file;  
    char        *append_file;     
    char        *heredoc_limiter;   
    struct s_cmd *next;  
} t_cmd;

typedef struct s_data
{
    char    **cmd_paths;
    char    **envp;
    char	**paths;
    char	*path;
    int		cmds;
    int	    *pipefds;
    pid_t	*pids;
} t_data;

void get_lexemes(t_list **lexemes, t_tokens **tokens, char *input);
void    get_expand_lexemes(t_list **lexemes, char *input);
void    get_normal_lexemes(t_list **lexemes, char *input);
int dollar_sign_check(char *input);
void	parse_tokens(t_tokens **tokens, t_cmd **cmd);
void    cmd_init(t_cmd **cmd);
void cleaning_func(t_tokens **tokens, t_list **lexemes, t_cmd **cmd);
void get_cmds_count(t_cmd **cmd, t_data *data);
void    get_pipefds(t_cmd **cmd, t_data *data);
void    process_pids(t_data *data, t_cmd **cmd);
char	*find_path(t_list *args, t_data *data);
char **args_to_array(t_cmd **cmd);
void	free_array(char **arr);
void	execute_one_cmd(t_cmd **cmd, t_data *data);
void    execute_basic_cmds(t_cmd **cmd, t_data *data, int cmd_index);
void free_cmd_list(t_cmd **cmd);
void free_data(t_data *data);

#endif