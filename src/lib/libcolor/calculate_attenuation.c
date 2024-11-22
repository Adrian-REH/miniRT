
#include "../../main.h"

double	calculate_attenuation(double distance, double k_c, \
	double k_l, double k_q)
{
	return (1.0 / (k_c + k_l * distance + k_q * distance * distance));
}
