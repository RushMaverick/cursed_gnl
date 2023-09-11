
#include "get_next_line.h"

static int ft_strlen(char *str)
{
	int i = 0;
	
	if (!str)
		return (0);
	while(str[i])
		i++;
	return (i);
}

static char *find_and_return_next(char **str, int *read_file)
{
    static char *start = NULL;
    static char *holder = NULL;

    if (!start && *str)
        start = *str;
    if (!*str)
        return (NULL);
    if (!holder)
        holder = *str;
   int size = 0;
   size = ft_strlen(holder);
   int k = 0;
    while (holder && holder[k])
        if(holder[k++] == '\n')
            break ;
    if(size == 0)
        return (NULL);
    if (k == size)
    {
        k = 0;
        char *final = malloc(sizeof(char) * (size + 1));
        while (holder && holder[k])
        {
            final[k] = holder[k];
            k++;
        }
        final[k] = '\0';
        free (start);
        *read_file = 0; 
        holder = NULL;
        start = 0;
        return (final);
    }
    else
    {
        char *final2 = malloc(sizeof(char) * (k + 1));
        k = 0;
        while (holder && holder[k])
        {
            final2[k] = holder[k];
            if (holder[k] == '\n')
            {
                holder = &holder[++k];
                break ;
            }
            k++;
        }
        final2[k] = '\0';
        return (final2);
    }
    return (NULL);
}
char *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    static char *buffer = NULL;
    static int  read_file = 0;
    if (read_file == 0)
	{
		int read_bytes = 0;
		int index = 0;
		buffer  = malloc(sizeof(char) * 20000);
		if (!buffer)
			return (NULL);
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0 || read_bytes < 0)
			return (NULL);
		while (read_bytes)
		{
            buffer[index + read_bytes] = '\0';
            index += read_bytes;
            read_bytes = read(fd, &buffer[index], BUFFER_SIZE);
		}
		buffer[index + read_bytes] = '\0';
        read_file = 1;
        return(find_and_return_next(&buffer, &read_file));
	}
    else
        return(find_and_return_next(&buffer, &read_file));
    return (NULL);
}
// int main(void)
// {
//     int fd = open("gnl.c", O_RDONLY);
//     char *str;
//     str = get_next_line(fd);
//     while (str)
//     {
//         write(1, str, ft_strlen(str));
//         write (1, "--hehe--\n", 9);
// 		free(str);
//         str = get_next_line(fd);
//     }
//     close(fd);
//     fd = open("text.txt", O_RDONLY);
//     str = get_next_line(fd);
//     while (str)
//     {
//         write(1, str, ft_strlen(str));
//         write (1, "--hehe--\n", 9);
// 		free(str);
//         str = get_next_line(fd);
//     }
//     close(fd);
//     return (0);
// }
