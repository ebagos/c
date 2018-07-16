```
/*
    数値を1桁ごとに配列に格納して計算する
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXKETA 11
#define MAXREP 1000

// 桁ごとに演算した後の桁あふれを1桁上に引き継ぐ
void normalize(int *x, int keta) {
    for (int i = 0; i < keta - 1; i++) {
        x[i + 1] += x[i] / 10;  // MAXKETA=10だとここにはifが必要になる
        x[i] %= 10;
    }
}

// 足し算
void plus(int *a, int *result, int keta) {
    for (int i = 0; i < keta; i++) {
        result[i] += a[i];
    }
    normalize(result, keta);
}

// べき乗
void power(int *x, int n, int keta) {
    x[0] = 1;   // 掛算なので初期値を1にしておく
                // ｎにしないのはロジックを単純化するため
    for (int th = 0; th < n; th++) {
        for (int i = 0; i < keta; i++) {
            x[i] *= n;
        }
        normalize(x, keta);
    }
}

// 表示用：関数化しておけばデバッグにも使える
void printout(int *val, int keta) {
    for (int i = keta - 2; i >= 0; i--) {
        printf("%d", val[i]);
    }
    printf("\n");
}

int main() {
    int result[MAXKETA];
    for (int i = 0; i < MAXKETA; i++) {
        result[i] = 0;
    }
    for (int i = 1; i <= MAXREP; i++) {
        int val[MAXKETA];
        for (int j = 0; j < MAXKETA; j++) {
            val[j] = 0;
        }
        power(val, i, MAXKETA);
        plus(val, result, MAXKETA);
    }
    printout(result, MAXKETA);
}

```
