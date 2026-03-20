#include "coders.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_isdigitstr(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);

		i++;
	}

	return (1);
}