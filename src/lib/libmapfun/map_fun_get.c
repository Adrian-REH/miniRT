#include "../../main.h"

t_map_fun map_fun_get(t_map_fun *map_fun, int key)
{
	int i;

	i = -1;
	while (map_fun[++i].key)
	{
		if (map_fun[i].key == key && map_fun[i].func)
			return map_fun[i];
	}
	return map_fun[i];
}
