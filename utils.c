#include "philo.h"

int	is_valid_number(char *s)
{
	int	index;

	index = 0;
	if (!s || !s[0])
		return (0);
	while (s[index])
	{
		if (s[index] < '0' || s[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

long	get_time_ms(void)
{
	struct	timeval tv;
	long	ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}