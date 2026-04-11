#include "coders.h"

void	coder_compile(t_coder *coder)
{
	int	first;
	int	second;

	get_dongle_lock_order(coder, &first, &second);
	pthread_mutex_lock(&coder->data->dongles[first].mutex);
	print_status(coder, "has taken a dongle");
	pthread_mutex_lock(&coder->data->dongles[second].mutex);
	print_status(coder, "has taken a dongle");
	update_compiling_at(coder);
	print_status(coder, "is compiling");
	ft_sleep(coder->data->time_to_compile);
	pthread_mutex_unlock(&coder->data->dongles[first].mutex);
	pthread_mutex_unlock(&coder->data->dongles[second].mutex);
}
