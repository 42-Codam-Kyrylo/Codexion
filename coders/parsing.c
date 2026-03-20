#include "coders.h"
#include <stdio.h>
#include <stdlib.h>

int	parse_int(char *value, int *out);

int	parse(t_data *data, int argc, char *argv[])
{
	if (argc != 9)
	{
		printf("ERROR: enter all arguments!\n");
		return (1);
	}
	if (parse_int(argv[1], &data->number_of_coders) != 0)
		return (1);
	return (0);
}

// long long	parse_milliseconds(char *value)
// {
// 	return
// }

int	parse_int(char *value, int *out)
{
	int	num;

	if (!ft_isdigitstr(value))
	{
		printf("ERROR: enter only digits!\n");
		return (1);
	}
	num = atoi(value);
	if (num <= 0)
	{
		printf("ERROR: enter positive value!\n");
		return (1);
	}
	*out = num;
	return (0);
}
