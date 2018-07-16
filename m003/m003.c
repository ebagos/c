/*
1ステートメントを実行し、かつそれを表示するマクロを作成せよ
*/
#include <stdio.h>

#define WARNING(x) do { (x); printf(#x); } while (0)

int main() {
    int a = 2, b = 3, c = 0;
    WARNING(a += 2);
    printf("a = %d b = %d c = %d\n", a, b, c);
}