/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:22:48 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/15 20:15:23 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void pipex(t_data *data, char **argv, char **envp)
{
    pid_t child_id;
    int i;

    i = 2;
    while (i < data->ac - 1)
    {
        printf("i == %d\n", i);
        if (pipe(data->pd) == -1)
            ft_print_error("Error in pipe()");
            //child_id[i]
        child_id = fork();
        if (child_id == -1)
            ft_print_error("Error in fork()");
        if (child_id == 0)
        {
            if (dup2(data->pd[0], 0) == -1)
                ft_print_error("Error in dup2()");
            close(data->pd[0]);
            if (i != data->ac - 2)
            {
                if (dup2(data->pd[1], 1) == -1)
                    ft_print_error("Error in dup2()");
                close(data->pd[1]);
            }
            else
            {
                printf("last i = %d\n", i);
                data->outfile = open(argv[data->ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
                if (data->outfile == -1)
                    ft_print_error("Error in open()");
                if (dup2(data->outfile, 1) == -1)
                    ft_print_error("Error in dup2()");
                close(data->outfile);
            }
            char **cmd = ft_split(argv[i], ' ');
            char *path = check_path(cmd[0], envp);
            execve(path, cmd, envp);
            ft_print_error("Error in execve()");
        }
        close(data->pd[0]);
        close(data->pd[1]);
        i++;
    }
    // parent waiting
    while (i < data->ac - 1)
    {
        wait(NULL);
        i--;
    }
    
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    if (!envp)
        ft_print_error("Error empty environement");
    if (argc >= 5)
    {
        data.ac = argc;
        pipex(&data, argv, envp);
    }
    else
        ft_print_error("Usage: ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2");
    return (0);
}
