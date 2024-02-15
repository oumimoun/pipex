/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 23:34:08 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/14 22:57:00 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char *check_path(char *cmd, char **envp)
{
    char **paths;
    char *full_path;
    int i;

    i = 0;
    if (access(cmd, F_OK | R_OK | X_OK) == 0)
        return cmd;
    paths = ft_get_paths(envp);
    while (paths && paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd);
        if (access(full_path, F_OK | R_OK | X_OK) == 0)
            return (full_path);
        free(full_path);
        full_path = NULL;
        i++;
    }
    return (NULL);
}

char **ft_get_paths(char **envp)
{
    char **path;
    int i;

    i = 0;
    path = NULL;
    while (envp[i])
    {
        if (ft_strncmp("PATH", envp[i], 4) == 0)
        {
            path = ft_split(envp[i] + 5, ':');
            return (path);
        }
        i++;
    }
    return (NULL);
}
