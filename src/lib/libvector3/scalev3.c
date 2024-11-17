#include "../../main.h"

Vector3 scalev3(Vector3 v, float scalar)
{
    return (Vector3) {
        v.x * scalar,
        v.y * scalar,
        v.z * scalar
    };
}