#include <stdio.h>
#include <stdlib.h>

int main() {
    const long MAXNUM = 1000;
    const long DIVR = 10000000000;
    long result = 0;
    for (long i = 1; i <= MAXNUM; i++) {
        long mul = i;
        for (long th = 1; th < i; th++) {
            mul = (mul * i) % DIVR;
        }
        result = (result + mul) % DIVR;
    }
    printf("The answer is %ld.\n", result);
}
