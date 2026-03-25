/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coders.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/24 20:16:39 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/03/25 20:30:49 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// compile -> debug -> refactor 

#ifndef CODERS_H
# define CODERS_H

#include <pthread.h>

typedef enum e_sched
{
	CODERS_SCHED_FIFO,
	CODERS_SCHED_EDF,
}				t_sched;

typedef struct s_dongle 
{
	pthread_mutex_t mutex;
	long long last_released_at;
} t_dongle;


typedef struct s_data
{
	int			number_of_coders;
	long long	time_to_burnout;
	long long	time_to_compile;
	long long	time_to_debug;
	long long	time_to_refactor;
	int			number_of_compiles_required;

	long long	dongle_cooldown;
	t_sched		scheduler;
}				t_data;

int				parse(t_data *data, int argc, char *argv[]);
int				ft_isdigit(int c);
int				ft_isdigitstr(char *s);
long long		ft_atoll(const char *str);

#endif

// // Примерная логика организации (без реализации парсинга)
// typedef struct s_data {
//     // Твои поля из конфига:
//     int number_of_coders;
//     long long time_to_burnout;
//     // ... остальное ...

//     // Новые поля для работы:
//     pthread_mutex_t *dongles;     // Массив мьютексов (донгалов)
//     pthread_mutex_t print_mutex;  // Мьютекс для вывода логов [cite: 199]
//     struct s_coder  *coders;      // Массив структур каждого кодера
// } t_data;

// typedef struct s_coder {
//     int id;
//     pthread_t thread;
//     t_data *all_data;             // Указатель обратно на общие настройки
// } t_coder;