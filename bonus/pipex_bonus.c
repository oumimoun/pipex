/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:22:48 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/21 16:15:40 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../get_next_line/get_next_line.h"

void ft_execute(t_data *data, char **argv, char **envp)
{
    char *path;
    char **cmd;

    cmd = ft_split(argv[data->i], ' ');
    path = check_path(cmd[0], envp);
    execve(path, cmd, envp);
    ft_print_error("Error in execve()");
}

void ft_parent_process(t_data *data)
{
    close(data->save);
    while (waitpid(-1, NULL, 0) != -1)
        ;
}

void ft_first_cmd(t_data *data, char **argv)
{
    data->infile = open(argv[1], O_RDONLY, 0777);
    if (data->infile == -1)
        ft_print_error("Error opening infile");
    if (dup2(data->infile, 0) == -1)
        ft_print_error("Error in dup2()");
    close(data->infile);
}

void ft_here_doc(void)
{
    int temp_fd = open("/tmp/temp_file", O_RDONLY);
    if (temp_fd == -1)
        ft_print_error("Error");
    if (dup2(temp_fd, 0) == -1)
        ft_print_error("Error in dup2()");
    close(temp_fd);
}

void ft_last_cmd(t_data *data, char **argv, char **envp)
{
    if (data->flag == 1)
        data->outfile = open(argv[data->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
    else
        data->outfile = open(argv[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (data->outfile == -1)
        ft_print_error("Error opening outfile");
    dup2(data->outfile, 1);
    close(data->outfile);
    ft_execute(data, argv, envp);
}

void middle_process(t_data *data, char **argv, char **envp)
{
    pid_t pid;

    if (pipe(data->pd) == -1)
        ft_print_error("Error in pipe()");
    pid = fork();
    if (pid == -1)
        ft_print_error("Error in fork()");
    if (pid == 0)
    { // child
        close(data->pd[0]);
        if (data->i == 2)
            ft_first_cmd(data, argv);
        if ((data->flag == 1) && data->i == 3)
            ft_here_doc();
        dup2(data->save, 0);
        if (data->i == data->ac - 2)
            ft_last_cmd(data, argv, envp);
        dup2(data->pd[1], 1);
        close(data->pd[1]);
        ft_execute(data, argv, envp);
    }
    close(data->save);
    data->save = dup(data->pd[0]);
    close(data->pd[0]);
    close(data->pd[1]);
}

void pipex(t_data *data, char **argv, char **envp)
{
    data->i = 2;
    data->save = -1;
    if (data->flag == 1)
        data->i = 3;
    while (data->i <= data->ac - 2)
    {
        middle_process(data, argv, envp);
        data->i++;
    }
    ft_parent_process(data);
}

void f(void)
{
    system("lsof -c pipex");
}


void ft_handle_here_doc(t_data *data, char **argv, char **envp)
{
    char *line = NULL;
    int temp_fd;

    data->LIMITER = argv[2];
    data->flag = 1;

    temp_fd = open("/tmp/temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (temp_fd == -1)
        ft_print_error("Error");    
    write(1, ">", 1);
    while ((line = get_next_line(0)) != NULL)
    {
        if (ft_strncmp(line, data->LIMITER, ft_strlen(data->LIMITER)) == 0)
        {
            free(line);
            break;
        }
        write(1, ">", 1);
        if (write(temp_fd, line, ft_strlen(line)) == -1)
        {
            free(line);
            close(temp_fd);
            unlink("/tmp/temp_file");
            ft_print_error("Error");
        }
        free(line);
    }
    close(temp_fd);
    pipex(data, argv, envp);
    unlink("/tmp/temp_file");
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    // atexit(f);

    if (argc == 1)
        ft_print_error("Usage: ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2");
    if (!envp)
        ft_print_error("Error empty environment");
    if (!ft_strncmp(argv[1], "here_doc", 9) && argc == 6)
    {
        data.ac = argc;
        ft_handle_here_doc(&data, argv, envp);
    }
    else if (argc >= 5)
    {
        data.ac = argc;
        data.flag = 0;
        pipex(&data, argv, envp);
    }
    else
        ft_print_error("Usage: ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2");
    return 0;
}
