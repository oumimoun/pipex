/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:52:57 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/17 23:48:30 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

#define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct s_data
{
    int infile;
    int outfile;
    int pd[2];
    int ac;
    int i;
    // pid_t child_id;
} t_data;

char **ft_split(char const *s, char c);
char *ft_strjoin(char *s1, char *s2);
char *check_path(char *cmd, char **envp);
char **ft_get_paths(char **envp);
int ft_strncmp(char *s1, char *s2, unsigned int n);
void ft_print_error(char *str);
int ft_strlen(char *str);
void ft_free(char **result);


#endif
