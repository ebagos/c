/*
与えられた2つの変数の値を入れ替えるマクロ（swapという名前とする）を作成し、動作確認プログラムを作成せよ。
なお、マクロの定義は動作確認プログラムと同一ソースで構わない。
*/

#include <stdio.h>

#define swap(a, b) \
    do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)
/*
    do {} while(0)で囲まないと、どうなるか
    {}で囲んだだけではどうなるか
*/

int main() {
    int a = 0, b = 1;
    printf("BEFORE: a = %d b = %d\n", a, b);
    swap(a, b);
    printf("AFTER : a = %d b = %d\n", a, b);

    double c = 1.0, d = 2.0;
    printf("BEFORE: c = %f d = %f\n", c, d);
    swap(c, d);
    printf("AFTER : c = %f d = %f\n", c, d);
}