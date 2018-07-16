/*
    数値を1桁ごとに配列に格納して計算する
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// 桁ごとに演算した後の桁あふれを1桁上に引き継ぐ
void normalize(uint64_t *x, uint64_t keta) {
    for (uint64_t i = 0; i < keta - 1; i++) {
        x[i + 1] += x[i] / 10;
        x[i] %= 10;
    }
    x[keta - 1] = 0;    // 下から11桁目の桁あふれを防ぐ（現状のC/C++ではエラーにならないが）
}

// 足し算
uint64_t* plus(uint64_t *a, uint64_t *result, uint64_t keta) {
    for (int i = 0; i < keta - 1; i++) {
        result[i] += a[i];
    }
    normalize(result, keta);
    return result;
}

// べき乗
uint64_t* power(uint64_t *x, uint64_t n, uint64_t keta) {
    x[0] = n;
    for (uint64_t th = 1; th < n; th++) {
        for (uint64_t i = 0; i < keta - 1; i++) {
            x[i] *= n;
        }
        normalize(x, keta);
    }
    return x;
}

// 表示用：関数化しておけばデバッグにも使える
void printout(uint64_t *val, uint64_t keta) {
    for (uint64_t i = keta - 2; i != 0; i--) {
        printf("%ld", val[i]);
    }
    printf("%ld\n", val[0]);
}

int main() {
    const uint64_t MAXKETA = 11;
    const uint64_t MAXREP = 1000;
    // int result[MAXKETA]としたほうがわかりやすいが、
    // メモリを確保できなかったときのエラーチェックができない
    uint64_t *result = (uint64_t *)calloc(MAXKETA, sizeof(uint64_t));
    if (result == NULL) {
        fprintf(stderr, "Not enough memory!\n");
        exit(-1);
    }
    uint64_t *val = (uint64_t *)calloc(MAXKETA, sizeof(uint64_t));
    if (val == NULL) {
        fprintf(stderr, "Not enough memory!\n");
        free(result);   // 正直コレが嫌い
        exit(-1);
    }
    for (int i = 1; i <= MAXREP; i++) {
        //int val[MAXKETA]; // 配列ならループ内でもいいかもだが、ヒープならループから出しておく
        for (uint64_t j = 0; j < MAXKETA; j++) {
            val[j] = 0;
        }
        //power(val, i, MAXKETA);
        plus(power(val, i, MAXKETA), result, MAXKETA);
    }
    free(val);
    
    printout(result, MAXKETA);

    free(result);
}
