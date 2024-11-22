#include "../../main.h"

Vector3	multiplyv3(Vector3 v, Vector3 u)
{
	return ((Vector3){
		v.x * u.x,
		v.y * u.y,
		v.z * u.z
	});
}
