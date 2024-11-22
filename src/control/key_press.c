#include "../main.h"

int	key_press(int key, void *param)
{
	static int		n_intent = 0;
	t_map_fun		map_fun;
	const t_map_fun	controls[10] = {
	{XK_a, (void (*)(void *))control_a},
	{XK_d, (void (*)(void *))control_d},
	{XK_w, (void (*)(void *))control_w},
	{XK_s, (void (*)(void *))control_s},
	{XK_Left, (void (*)(void *))control_left},
	{XK_Up, (void (*)(void *))control_up},
	{XK_Right, (void (*)(void *))control_right},
	{XK_Down, (void (*)(void *))control_down},
	{XK_Escape, (void (*)(void *))control_escape},
	{0, NULL}
	};

	if (n_intent >= 1)
		return (0);
	map_fun = map_fun_get(controls, key);
	if (map_fun.func)
	{
		n_intent++;
		map_fun.func(param);
		n_intent--;
	}
	return (0);
}
