/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:44:46 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/08 18:47:13 by ana-pdos         ###   ########.fr       */
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
    int i;

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
            get_cmds_count(&cmd, &data);
            data.cmd_paths = malloc((data.cmds + 1) * sizeof(char *));
            if (!data.cmd_paths)
                return (1);
            temp = cmd;
            i = 0;
            while (temp)
            {
                args_temp = temp->args;
                while (args_temp)
                {
                    printf("Arg: %s\n", (char *)args_temp->content);
                    data.cmd_paths[i] = find_path(args_temp, &data);
                    break ;
                }
                i++;
                temp = temp->next;
            }
            data.cmd_paths[i] = NULL;
            get_pipes_pids(&cmd, &data);
        }
        free(input);
        cleaning_func(&tokens, &lexemes, &cmd);
        cmd_init(&cmd);
    }
    return 0;
}



