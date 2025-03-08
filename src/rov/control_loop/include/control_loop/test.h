#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct demo {
    int apples;
    int oranges;
    char *fruit_name;
} demo;

demo *make_demo(int a, int o, const char *f) {
    demo *d = (demo *)malloc(sizeof(demo));  // Correct struct allocation
    if (d != NULL) {
        d->apples = a;
        d->oranges = o;

        // Allocate memory for the string and copy it
        d->fruit_name = strdup(f);  // Equivalent to malloc + strcpy
        if (d->fruit_name == NULL) {
            free(d);  // Cleanup if allocation fails
            return NULL;
        }
    }
    return d;
}

void free_demo(demo *d) {
    if (d != NULL) {
        free(d->fruit_name);  // Free allocated string
        free(d);  // Free struct
    }
}
