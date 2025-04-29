/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:21:38 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 15:56:26 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

char	*get_next_line(int fd);
int		ft_strchr(char	*s, int c);
char	*ft_strjoin(char *start, char *buff);
char	*ft_complete(char *dest, char *start, char *buffer);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*zyalloc(long long size);
int     ft_strncmp(const char *str1, const char *str2, size_t num);
#endif