#	ifndef LIBFT_H
#	define LIBFT_H

#include <stddef.h>

int ft_atoi(char *str);
void *ft_calloc(size_t nmemb, size_t size);
void ft_itoa(char *str, int n);
size_t ft_strlen(const char *s);
void *ft_memcpy(void *dest, const void *src, int n);

#	endif
