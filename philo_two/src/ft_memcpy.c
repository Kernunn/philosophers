#include "libft.h"

void *ft_memcpy(void *dest, const void *src, int n) {
  int k;
  unsigned char *restrict
  s1;
  unsigned char *restrict
  s2;

  s1 = (unsigned char *) dest;
  s2 = (unsigned char *) src;
  k = 0;
  while (k < n) {
	*s1++ = *s2++;
	++k;
  }
  return (dest);
}
