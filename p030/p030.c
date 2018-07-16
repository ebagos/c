/*
驚くべきことに, 各桁を4乗した数の和が元の数と一致する数は3つしかない.

    1634 = 1^4 + 6^4 + 3^4 + 4^4
    8208 = 8^4 + 2^4 + 0^4 + 8^4
    9474 = 9^4 + 4^4 + 7^4 + 4^4

ただし, 1=1^4は含まないものとする. この数たちの和は 1634 + 8208 + 9474 = 19316 である.

各桁を5乗した数の和が元の数と一致するような数の総和を求めよ.
*/

#include <stdio.h>

// べき乗計算 x^n
int powi(int x, int n) {
    int rc = 1;
    for (int i = 0; i < n; i++) {
        rc *= x;
    }
    return rc;
}

// 同じ数字nがc桁の数値作成
int fill(int n, int c) {
    int sum = 0;
    for (int i = 0; i < c; i++) {
        sum = sum * 10 + n;
    }
    return sum;
}

/*  各桁をn乗した数が取りうる最大値
    9のべき乗の桁数個分足したのがその桁での最大値（右辺）
    この値より、9並びの数値が大きくなると
    候補となる数値は現れない
*/
int limit(int n) {
    int tmp;
    for (int i = 1; ; i++) {
        tmp = fill(9, i);
        if (tmp > i * powi(9, n)) break;
    }
    return tmp;
}

// 与えられた数値の各桁をc乗し、足し合わせの計算
int sop(int n, int c) {
    int sum = 0;
    while (n > 0) {
        sum += powi( n % 10, c);
        n /= 10;
    }
    return sum;
}

int main() {
    int sum = 0;
    for (int i = 2; i < limit(5); i++) {
      if (i == sop(i, 5)) {
        sum += i;
      }
    }
    printf("ans.= %d\n", sum);
  }
  