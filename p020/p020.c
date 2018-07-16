/*
n × (n - 1) × ... × 3 × 2 × 1 を n! と表す.

例えば, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800 となる.
この数の各桁の合計は 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27 である.

では, 100! の各桁の数字の和を求めよ.
*/
/*
    現仕様のC言語では何らかの特殊な拡張がない限り解は出せないはず
*/
#include <stdio.h>
#include <stdint.h>

uintmax_t factorial(uintmax_t n) {
    uintmax_t rc = 1;
    for (uintmax_t i = n; i > 0; i--) {
        rc *= i;
        printf("%jd\n", rc);
    }
    return rc;
}

uintmax_t nsum(uintmax_t n) {
    uintmax_t sum = 0;
    while (n > 0) {
        sum += (n % 10);
        n /= 10;
    }
    return sum;
}

int main() {
    printf("100 => %jd\n", factorial(100));
    printf("100 => %jd\n", nsum(factorial(100)));
}