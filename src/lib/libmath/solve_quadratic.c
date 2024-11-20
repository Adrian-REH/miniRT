#include "../../main.h"

int solve_quadratic(double a, double b, double c, double* t0, double* t1)
{
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return 0;
    
    double q = (b > 0) ? -0.5 * (b + sqrt(discriminant)) : -0.5 * (b - sqrt(discriminant));
    *t0 = q / a;
    *t1 = c / q;
    
    if (*t0 > *t1) {
        double temp = *t0;
        *t0 = *t1;
        *t1 = temp;
    }
    
    return 1;
}
