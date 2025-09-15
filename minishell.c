/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:44:46 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/15 16:59:49 by ana-pdos         ###   ########.fr       */
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
    (void)argc;
    tokens = NULL;
    lexemes = NULL;
    data.envp = envp;
    cmd_init(&cmd);
	while (1)  
	{
        i = 0;
        cmd->index_args_array = 0;
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
                return (cleaning_func(&tokens, &lexemes, &cmd), free_data(&data), 1);
            temp = cmd;
            while (temp)
            {
                args_temp = temp->args;
                temp->args_array = args_to_array(&temp); 
                data.cmd_paths[i] = find_path(args_temp, &data);
                i++;
                temp = temp->next;
            }
            data.cmd_paths[i] = NULL;
            get_pipefds(&cmd, &data);
            process_pids(&data, &cmd);
        }
        free(input);
        free_array(data.cmd_paths);
        free(data.pipefds);
        free(data.pids);
        cleaning_func(&tokens, &lexemes, &cmd);
        cmd_init(&cmd);
    }
    return 0;
}


