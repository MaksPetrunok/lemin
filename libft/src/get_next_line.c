/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:30:11 by mpetruno          #+#    #+#             */
/*   Updated: 2018/08/30 15:51:05 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	set_rem_buff(t_list **rem, int fd, char *str)
{
	t_list	*cur;
	t_rem	*tmp;

	if (str == 0 || *str == '\0')
		return (0);
	cur = *rem;
	while ((tmp = 0) == 0 && cur)
	{
		if ((tmp = (t_rem *)(cur->content)) && tmp->id == fd)
		{
			free((void *)(tmp->str));
			return ((tmp->str = str) != 0);
		}
		cur = cur->next;
	}
	if ((tmp = (t_rem *)malloc(sizeof(t_rem))) == 0)
		return (-1);
	tmp->id = fd;
	tmp->str = str;
	if (*rem)
		ft_lstadd(rem, ft_lstnew((void *)tmp, sizeof(t_rem)));
	else
		*rem = ft_lstnew((void *)tmp, sizeof(t_rem));
	free((void *)tmp);
	return (1);
}

static int	append_buff(char *buff, char **str, int fd, t_list **rem)
{
	size_t	i;
	char	*tmp;
	char	flag;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	flag = (buff[i] == '\n');
	buff[i] = '\0';
	if (*str != 0)
	{
		if (i != 0 && (tmp = ft_strjoin(*str, buff)) == 0)
			return (-1);
		if (i == 0 && (tmp = ft_strdup(*str)) == 0)
			return (-1);
	}
	else
		tmp = (i != 0) ? ft_strdup(buff) : ft_strnew(0);
	free((void *)(*str));
	*str = tmp;
	if (flag && buff[i + 1] != '\0')
		set_rem_buff(rem, fd, ft_strdup(buff + i + 1));
	return (flag);
}

static int	get_rem(int fd, t_list *rem, char **str)
{
	t_rem	*tmp;
	char	*s;
	size_t	i;
	int		flag;

	while (rem)
		if (((t_rem *)(rem->content))->id == fd)
			break ;
		else
			rem = rem->next;
	if (rem == 0)
		return (0);
	tmp = (t_rem *)(rem->content);
	if ((s = tmp->str) == 0 || *s == '\0')
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	tmp->str = 0;
	if ((flag = (s[i] == '\n')) && s[i + 1] != '\0')
		tmp->str = ft_strdup(s + i + 1);
	s[i] = '\0';
	*str = ft_strdup(s);
	free((void *)s);
	return (flag);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*rem_buff;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				n;
	int				append;

	tmp = 0;
	if (get_rem(fd, rem_buff, &tmp))
	{
		*line = tmp;
		return (1);
	}
	while ((n = read(fd, &buff, BUFF_SIZE)) > 0)
	{
		buff[n] = '\0';
		if ((append = append_buff(buff, &tmp, fd, &rem_buff)) == 1)
			*line = tmp;
		if (append == 1 || append == -1)
			return (append);
	}
	if (n == -1)
		return (-1);
	*line = (tmp == 0) ? ft_strnew(0) : tmp;
	return (tmp != 0);
}
