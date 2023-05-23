#include "../minishell.h"

char *getstr(char *src)
{
    char    *dst;
    int     i;

    dst = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
    if (!dst)
        return (NULL);
    i = -1;
    while(src[++i])
        dst[i] = src[i];
    dst[i] = '\0';
    return (dst); 
}