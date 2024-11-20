#include "../main.h"

int	key_press(int key, void *param)
{
	static	n_intent = 0;
	t_map_fun	map_fun;
	const t_map_fun	controls[10] = {
		{XK_a, control_a},
		{XK_d, control_d},
		{XK_w, control_w},
		{XK_s, control_s},
		{XK_Left, control_left},
		{XK_Up, control_up},
		{XK_Right, control_right},
		{XK_Down, control_down},
		{XK_Escape, control_escape},
		{0, NULL}
	};
	//FIX IT FUNCTIONS WITHIN HORIZONTAL CAMERA AND VERTICAL CAMERA VECTOR3

	if (n_intent >= 1)
		return 0;
	map_fun = map_fun_get(controls, key);
	if (map_fun.func)
	{
		n_intent++;
		map_fun.func(param);
		n_intent--;
	}
	return (0);
}
