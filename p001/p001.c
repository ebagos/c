/*
  1以上、1000未満の整数で、3または5で割り切れるものの和を求める
  複数の解決法を提示し、評価せよ
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MIN 1
#define MAX 1000

// 一般的なC/C++プログラム
uintmax_t p001_1() {
  uintmax_t sum = 0;
  for (uintmax_t i = MIN; i < MAX; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }
  }
  return sum;
}

/*
  仕様変更があったら大変、パラメータ化しようとして、だいたい以下の関数をつくることになる
*/
uintmax_t p001_2(uintmax_t min, uintmax_t max, uintmax_t md1, uintmax_t md2) {
  uintmax_t sum = 0;
  for (uintmax_t i = min; i < max; i++) {
    if (i % md1 == 0 || i % md2 == 0) {
      sum += i;
    }
  }
  return sum;
}

/*
  汎用関数ができたと鼻高々になる
  実際には検査項目を増やしただけな気がする

  与えられた命題を汎用化すると
  「ある範囲の数列に対して、ある条件でフィルタリングした後、特定の演算を施せ」
  であるから、パラメータは
    範囲数値を表現したもの（何かの集合）
    フィルタリング条件
    演算
  を与え、その結果を返すべき
*/
bool filter(uintmax_t n) {
    if (n % 3 == 0 || n % 5 == 0) {
        return true;
    } else {
        return false;
    }
}

uintmax_t func(uintmax_t in, uintmax_t rc) {
    return in + rc;
}

uintmax_t p001_3(uintmax_t min, uintmax_t max) {
    uintmax_t rc = 0;
    for (uintmax_t i = min; i < max; i++) {
        if (filter(i)) rc = func(i, rc);
    }
    return rc;
}
/*
uintmax_t p001_4(uintmax_t min, uintmax_t max, uintmax_t n) {
    if (min == max) return n;
    if (filter(min)) return p001_4(min + 1, max, func(min, n));
    return p001_4(min + 1, max, n);
}
*/
uintmax_t func2(uintmax_t in, uintmax_t rc) {
    if (filter(in)) {
        return rc + in;
    } else {
        return rc;
    }
}

uintmax_t p001_5(uintmax_t min, uintmax_t max, uintmax_t n) {
    if (min == max) return n;
    return p001_5(min + 1, max, func2(min, n));
}

int main() {
    if (MAX > INTMAX_MAX / (MAX - MIN + 1) * 2 - MIN) {
        printf("Error: maybe overflow\n");
        return 1;
    }
    printf("%jd\n", p001_1());
    printf("%jd\n", p001_2(MIN, MAX, 3, 5));
    printf("%jd\n", p001_3(MIN, MAX));
//    printf("%jd\n", p001_4(MIN, MAX, 0));
    printf("%jd\n", p001_5(MIN, MAX, 0));
    return 0;
}
