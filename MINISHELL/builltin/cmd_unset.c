
#include <stdlib.h> // For malloc and free
#include <unistd.h> // For write and close
#include <fcntl.h>  // For open
#include <string.h> 
#include <stddef.h> 
#include <stdio.h>


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strwdup(char *str, int len)
{
	char	*array;
	int		count;

	if (!str || !len)
		return (NULL);
	count = -1;
	array = (char *)malloc((len + 1) * sizeof(char));
	while (++count < len)
		array[count] = str[count];
	array[count] = '\0';
	return (array);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	int		len;
	char	*array;

	i = 0;
	len = ft_strlen(s2);
	if (!s1)
		return (ft_strwdup(s2, len));
	len = len + ft_strlen(s1);
	array = (char *)malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	len = 0;
	while (s1[i] != '\0')
		array[len++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		array[len++] = s2[i++];
	array[len] = '\0';
	free(s1);
	return (array);
}

int	openfd(char **ev)
{
	int		i;
	int		found;
	int		fd;
	char	*path;

	i = -1;
	found = 0;
	while (ev[++i])
	{
		if (!ft_strncmp("BASEDIR=", ev[i], 8))
		{
			found = 1;
			break ;
		}
	}
	if (found == 0)
		return (-1);
	found = ft_strlen(ev[i] + 8);
	path = ft_strwdup(ev[i] + 8, found - 1);
	path = ft_strjoin(path, "/.env");
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(path);
	return (fd);
}

int	to_unset(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **ev)
{
	int	i;
	int	fd;

	i = 0;
	if (ac != 2)
		return (printf("unset: not enough arguments\n"), 0);
	if (!to_unset(av[1]))
		return (0);
	fd = openfd(ev);
	while (ev[i])
	{
		if (!ft_strncmp(av[1], ev[i], ft_strlen(av[1])))
			i++;
		write(fd, ev[i], ft_strlen(ev[i]));
		i++;
	}
	close(fd);
	return (0);
}