#include <limits.h>
#include <float.h>

#include <stdio.h>

int main() {
    int i = INT_MAX;
    float f = FLT_MAX;
    double d = DBL_MAX;

    printf("int   : %lu -> %i\n", sizeof(i), i);
    printf("float : %lu -> %f\n", sizeof(f), f);
    printf("double: %lu -> %f\n", sizeof(d), d);

    return 0;
}
