#include "../../main.h"

Vector3 add_vector3_to_vector3(Vector3 init, Vector3 end)
{
    return (Vector3) {
        init.x + end.x,
        init.y + end.y,
        init.z + end.z
    };
}

Vector3 add_scalar_to_vector3(Vector3 init, double scale)
{
    return (Vector3) {
        init.x + scale,
        init.y + scale,
        init.z + scale
    };
}