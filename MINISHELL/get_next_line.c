#include "minishell.h"
size_t	gnl_strlen(const char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = gnl_strlen(s);
	i = 0;
	if (len > s_len)
		len = s_len;
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	while (i++ < start)
		s++;
	gnl_strlcpy(substr, s, len + 1);
	return (substr);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			size_src;

	i = 0;
	if (src == NULL)
		return (0);
	size_src = gnl_strlen(src);
	if ((int)size < 0)
		size = size_src + 1;
	if (size >= 2 && size_src != 0)
	{
		while (i < size - 1)
		{
			if (i < size_src)
				dst[i] = src[i];
			else if (i == size_src)
				dst[i] = '\0';
			i++;
		}
	}
	if (size != 0)
		dst[i] = '\0';
	return (size_src);
}

int	gnl_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

size_t	gnl_strlcat(char *dst, const char *src, size_t size)
{
	char			*ptr;
	unsigned int	i;

	if (size < gnl_strlen(dst))
		return (gnl_strlen(src) + size);
	ptr = dst + gnl_strlen(dst);
	i = gnl_strlen(dst);
	while (i < size - 1 && *src != '\0' && size >= 2)
	{
		*ptr = *src;
		ptr++;
		src++;
		i++;
	}
	if (size != 0)
		*ptr = '\0';
	return (gnl_strlen(dst) + gnl_strlen(src));
}
char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*line;
	size_t		old_len;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	if (gnl_strchr_i(buf[fd], '\n') == -1)
	{
		old_len = gnl_strlen(buf[fd]);
		buf[fd] = gnl_expand_buffer(buf[fd], fd);
		if (old_len == gnl_strlen(buf[fd]) && buf[fd])
			line = gnl_substr(buf[fd], 0, gnl_strlen(buf[fd]));
	}
	if (!buf[fd])
		return (NULL);
	if (!line && gnl_strchr_i(buf[fd], '\n') != -1)
		line = gnl_substr(buf[fd], 0, gnl_strchr_i(buf[fd], '\n') + 1);
	if (line)
	{
		buf[fd] = gnl_shrink_buffer(buf[fd], line);
		return (line);
	}
	return (get_next_line(fd));
}

char	*gnl_shrink_buffer(char *buf, char *line)
{
	char	*newbuf;
	int		line_len;

	if (!buf || !line)
		return (buf);
	line_len = gnl_strlen(line);
	if ((int)gnl_strlen(buf) == line_len)
	{
		free(buf);
		return (NULL);
	}
	newbuf = gnl_substr(buf, line_len, gnl_strlen(buf) - line_len);
	free(buf);
	return (newbuf);
}

char	*gnl_expand_buffer(char *buf, int fd)
{
	char	*newbuf;
	int		newlen;
	char	*aux;

	aux = gnl_newread(fd);
	if (!aux)
		return (NULL);
	if (!aux[0])
	{
		free(aux);
		return (buf);
	}
	if (!buf)
		return (aux);
	newlen = gnl_strlen(buf) + gnl_strlen(aux);
	newbuf = malloc(newlen + 1);
	if (!newbuf)
		return (NULL);
	gnl_strlcpy(newbuf, buf, newlen + 1);
	gnl_strlcat(newbuf, aux, newlen + 1);
	free(buf);
	free(aux);
	return (newbuf);
}

char	*gnl_newread(int fd)
{
	char	*aux;
	int		nbytes;

	aux = malloc(BUFFER_SIZE + 1);
	if (!aux)
		return (NULL);
	nbytes = read(fd, aux, BUFFER_SIZE);
	if (nbytes < 0)
	{
		free(aux);
		return (NULL);
	}
	aux[nbytes] = '\0';
	return (aux);
}
