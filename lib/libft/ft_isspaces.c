#include "libft.h"

int	ft_isspaces(char str)
{
	return ((str <= 13 && str >= 9) || str == ' ');
}
