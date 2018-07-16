/*
    数値を1桁ごとに配列に格納して計算する
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAXREP 1000
#define DIVR 10000000000

// 足し算
uint64_t plus(uint64_t x, uint64_t result) {
    return (x + result) % DIVR;
}

// べき乗
uint64_t power(uint64_t x, uint64_t n) {
    for (uint64_t th = 1; th < n; th++) {
        x = (x * n) % DIVR;
    }
    printf("%ld - %lu\n", n, x);
    return x;
}

bool checker(uint64_t reps, uint64_t dsr) {
    const uint64_t checkrep = 1000;
    const uint64_t checkdivr = 10000000000;

    if (reps > checkrep || dsr > checkdivr) {
        return false;
    } else {
        return true;
    }
}

int main() {
    if (checker(MAXREP, DIVR) == false) {
        fprintf(stderr, "Bad parameter(s).\n");
        exit(-1);
    }

    uint64_t result = 0;
    for (uint64_t i = 1; i <= MAXREP; i++) {
        result = plus(power(i, i), result);
    }
    printf("%lu\n", result);
}
