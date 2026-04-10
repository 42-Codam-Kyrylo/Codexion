#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((long long)tv.tv_sec * 1000 + (tv.tv_usec / 1000));
	// total_ms = (seconds *1000) + (microseconds / 1000)
}

int	main(void)
{
	long long start_time;
	long long elapsed;

	start_time = get_current_time();

	usleep(505 * 1000);

	elapsed = get_current_time() - start_time;
	printf("Time passed: %lld ms\n", elapsed);
	return (0);
}