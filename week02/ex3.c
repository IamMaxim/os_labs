#include <stdio.h>

#define pine 0
#define right_triangle 1
#define laying_pine 2
#define brick 3

void usage() {
    printf("Usage:\n");
    printf("\tex3 <size> [type]\n");
    printf("Types can be:\n");
    printf("\t0 - Pine\n");
    printf("\t1 - Right triangle\n");
    printf("\t2 - Laying pine\n");
    printf("\t3 - Brick\n");
}

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3) {
        usage();
        return 1;
    }

    // Type of the shape
    int type = 0;
    // Parse shape type, if any is provided
    if (argc == 3) {
        sscanf(argv[2], "%i", &type);
    }

    // Check if entered type is valid
    if (type < 0 || type > 3) {
        printf("You passed invalid type. Refer to usage:\n");
        usage();
        return 1;
    }

    int size;
    sscanf(argv[1], "%i", &size);

    switch (type) {

    case pine: {
        for (int i = 0; i < size; i++) {
            // Print left padding
            for (int j = 0; j < size - i; j++)
                printf(" ");

            // Print main part
            for (int j = 0; j < i * 2 + 1; j++)
                printf("*");

            printf("\n");
        }

        break;
    }

    case right_triangle: {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < i + 1; j++)
                printf("*");
            printf("\n");
        }

        break;
    }

    case laying_pine: {
        for (int i = 0; i < size; i++) {
            int k = i;
            if (k >= size / 2)
                k = size - i - 1;

            for (int j = 0; j < k + 1; j++)
                printf("*");

            printf("\n");
        }

        break;
    }

    case brick: {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                printf("*");
            printf("\n");
        }

        break;
    }
    }

    return 0;
}
