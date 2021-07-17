#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ans;

	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ans = malloc(size * nmemb);
	if (ans)
		return (memset(ans, '\0', size * nmemb));
	return (NULL);
}
