/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:44:46 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/08 12:53:07 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main (int argc, char **argv, char **envp)
{
	char *input;
    t_tokens *tokens;
    t_list *lexemes;
    t_data data;
    t_cmd *cmd;
    t_cmd *temp;
    t_list *args_temp;

    (void)argv;
    if (argc != 1)
        return (1);
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
            temp = cmd;
            while (temp)
            {
                args_temp = temp->args;
                while (args_temp)
                {
                    printf("Arg: %s\n", (char *)args_temp->content);
                    find_path(args_temp, &data);
                    break ;
                }
                temp = temp->next;
            }
            get_pids(&cmd, data.pids, data.pipefds);
        }
        free(input);
        cleaning_func(&tokens, &lexemes, &cmd);
        cmd_init(&cmd);
    }
    return 0;
}



