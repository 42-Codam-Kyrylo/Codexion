#include "coders.h"

static void	take_dongle(t_coder *coder, int idx);
static void	release_dongle(t_coder *coder, int idx);
static int	can_take_dongle(t_dongle *dongle, t_coder *coder);

/**
 * @brief Performs one full compile cycle for a coder.
 *
 * Locks both required dongles in deterministic order, compiles,
 * then releases both dongles.
 *
 * @param coder Current coder.
 */
void	coder_compile(t_coder *coder)
{
	int	first;
	int	second;

	get_dongle_lock_order(coder, &first, &second);
	take_dongle(coder, first);
	take_dongle(coder, second);
	update_compiling_at(coder);
	print_status(coder, "is compiling");
	ft_sleep(coder->data->time_to_compile);
	release_dongle(coder, first);
	release_dongle(coder, second);
}

/**
 * @brief Requests and acquires one dongle using scheduler priority.
 *
 * Pushes the coder into the dongle wait-queue and waits on the condition
 * variable until this coder can take the dongle.
 *
 * @param coder Current coder.
 * @param idx Dongle index to take.
 */
static void	take_dongle(t_coder *coder, int idx)
{
	t_dongle	*dongle;

	dongle = &coder->data->dongles[idx];
	pthread_mutex_lock(&dongle->mutex);
	t_node node = {
		.coder_id = coder->id,
		.priority = get_node_priority(coder),
	};
	insert_heap(dongle->queue, node);
	while (!can_take_dongle(dongle, coder))
	{
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	dongle->status = DONGLE_OCCUPIED;
	print_status(coder, "has taken a dongle");
	pop_heap(dongle->queue);
	pthread_mutex_unlock(&dongle->mutex);
}

/**
 * @brief Releases one dongle and wakes waiting coders.
 *
 * Marks the dongle as free, updates release time, and broadcasts the
 * condition variable so queued coders can re-check acquisition conditions.
 *
 * @param coder Current coder.
 * @param idx Dongle index to release.
 */
static void	release_dongle(t_coder *coder, int idx)
{
	t_dongle	*dongle;

	dongle = &coder->data->dongles[idx];
	pthread_mutex_lock(&dongle->mutex);
	dongle->status = DONGLE_FREE;
	dongle->last_released_at = get_current_time();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

static int	can_take_dongle(t_dongle *dongle, t_coder *coder)
{
	long elapsed;

	elapsed = get_current_time() - dongle->last_released_at;
	return (dongle->status == DONGLE_FREE
		&& elapsed > coder->data->dongle_cooldown
		&& dongle->queue->array[0].coder_id == coder->id);
}