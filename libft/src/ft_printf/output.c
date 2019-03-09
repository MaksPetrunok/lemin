/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:37:56 by mpetruno          #+#    #+#             */
/*   Updated: 2018/10/23 13:41:44 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flush(t_outbuff *buff)
{
	buff->count += write(buff->fd, buff->buffer, buff->end - buff->buffer);
	buff->end = buff->buffer;
}

void	appendchr(t_outbuff *buff, const char c, int n)
{
	while ((buff->end - buff->buffer) < OUTPUT_BUFF_SIZE && n != 0)
	{
		*(buff->end++) = c;
		n--;
	}
	if (n != 0)
	{
		flush(buff);
		appendchr(buff, c, n);
	}
}

void	append(t_outbuff *buff, const char *str, int n)
{
	while ((buff->end - buff->buffer) < OUTPUT_BUFF_SIZE && *str && n != 0)
	{
		*(buff->end++) = *str++;
		n--;
	}
	if (*str && n != 0)
	{
		flush(buff);
		append(buff, str, n);
	}
}

void	initialize_output_buff(t_outbuff *buff, int fd)
{
	buff->fd = fd;
	buff->count = 0;
	buff->buffer[0] = '\0';
	buff->end = buff->buffer;
}

void	appendnchr(t_outbuff *buff, const char *str, int n)
{
	while ((buff->end - buff->buffer) < OUTPUT_BUFF_SIZE && n != 0)
	{
		*(buff->end++) = *str++;
		n--;
	}
	if (*str && n != 0)
	{
		flush(buff);
		append(buff, str, n);
	}
}
