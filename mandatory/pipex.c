/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:09:43 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/22 20:20:01 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void f()
{
    system("lsof -c pipex");
}

void *second_process(t_data *data, char **argv, char **envp)
{
    char *path;
    char **cmd;

    close(data->pd[1]);
    data->outfile = open(argv[4], O_CREAT | O_RDONLY | O_WRONLY , 0777);
    if(data->outfile == -1)
        return (ft_print_error("Error in open()") , close(data->pd[0]) , NULL);
    if (dup2(data->outfile, 1) == -1)
        return (ft_print_error("Error in dup2()"), close(data->outfile), NULL);
    if (dup2(data->pd[0], 0) == -1)
    {
        close(data->outfile);
        close(data->pd[0]);
        return (ft_print_error("Error in dup2()"), NULL);
    }
    close(data->pd[0]);
    cmd = ft_split(argv[3], ' ');
    path = check_path(cmd[0], envp);
    close(data->outfile);
    execve(path, cmd, envp);
    ft_print_error("Error in execve()");
    return (ft_free(cmd), free(path), path = NULL, NULL);
}

void *first_process(t_data *data, char **argv, char **envp)
{
    char **cmd;
    char *path;

    close(data->pd[0]);
    data->infile = open(argv[1], O_RDONLY);
    if (data->infile == -1)
    {
        close(data->pd[1]);
        return (ft_print_error("Error in open()"), NULL);
    }
    if (dup2(data->infile, 0) == -1)
        return (ft_print_error("Error in dup2()"), close(data->infile), NULL);
    if (dup2(data->pd[1], 1) == -1)
    {
        close(data->infile);
        close(data->pd[1]);
        return (ft_print_error("Error in dup2()"), NULL);
    }
    close(data->pd[1]);
    cmd = ft_split(argv[2], ' ');
    path = check_path(cmd[0], envp);
    close(data->infile);
    execve(path, cmd, envp);
    ft_print_error("Error in execve()");
    return (ft_free(cmd), free(path), path = NULL, NULL);
}

void pipex(t_data *data, char **argv, char **envp)
{
    int status;
    pid_t child1_id;
    pid_t child2_id;

    if (pipe(data->pd) == -1)
        ft_print_error("Error in pipe()");
    child1_id = fork();
    if (child1_id == -1)
        ft_print_error("Error in fork()");
    if (child1_id == 0)
        first_process(data, argv, envp);
    child2_id = fork();
    if (child2_id == -1)
        ft_print_error("Error in fork()");
    if (child2_id == 0)
        second_process(data, argv, envp);

    close(data->pd[0]);
    close(data->pd[1]);

    waitpid(child1_id, &status, 0);
    waitpid(child2_id, &status, 0);
}

void leak(void)
{
    system("leaks pipex");
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
    atexit(f);
    if (!envp)
        ft_print_error("Error empty environement");
    if (argc != 5)
        ft_print_error("Usage: ./pipex file1 cmd1 cmd2 file2");
    pipex(&data, argv, envp);

    return (0);
}
