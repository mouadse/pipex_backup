/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:14:33 by msennane          #+#    #+#             */
/*   Updated: 2024/07/28 23:14:34 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

char	**ft_split(char const *s, char sep);
void	ft_putstr_fd(char *str, int fd);
int		ft_strncmp(char *str1, char *str2, int n);
char	*ft_strdup(const char *str);
char	*ft_strjoin_three(char *str1, char *str2, char *str3);
char	*ft_strjoin(char *str1, char *str2);
int		ft_strlen(const char *str);
#endif
