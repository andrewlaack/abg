#include <assert.h>
#include <stdlib.h>

int choose_random(int length) {
    int rnd1 = ((rand() % length) + length) % length;
    assert(rnd1 >= 0);
    assert(rnd1 < length);
    return rnd1;
}

