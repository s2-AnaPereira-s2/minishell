/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:44:46 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/05 17:13:48 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main (int argc, char **envp)
{
	char *input;
    t_tokens *tokens;
    t_list *lexemes;
    t_data data;
    t_cmd *cmd;

    (void)argc;  // Mark as unused to avoid compiler warning
    tokens = NULL;
    lexemes = NULL;
    data.envp = envp;
    cmd_init(&cmd);
    
	while (1)  
	{
        input = readline("bbshell> ");
        if (!input)
            break;
        if (*input)
        {
            add_history(input);
            get_lexemes(&lexemes, &tokens, input);
            parse_tokens(&tokens, &cmd);
        }
        free(input);
        cleaning_func(&tokens, &lexemes);
        cmd_init(&cmd);
    }
    return 0;
}
