/*
2520 は 1 から 10 の数字の全ての整数で割り切れる数字であり, そのような数字の中では最小の値である.
では, 1 から 20 までの整数全てで割り切れる数字の中で最小の正の数はいくらになるか.
*/
/*
    unsigned によって負の値を排除
    ０か否かのチェックが必要
    本問題に合わせてunsigned intにしたが、ビット数を増やす考慮も必要
*/

#include <stdio.h>

unsigned int gcd(unsigned int a, unsigned int b)
{
    unsigned int tmp;
    if (a == 0 || b == 0) {
        return 0;
    }
    // ユークリッドの互除法のまま
    while ((tmp = a % b) != 0) {
        a = b;
        b = tmp;
    }
    return b;
}

unsigned int lcm(unsigned int a, unsigned int b) {
    if ( a == 0 || b == 0)
    return 0;

    return (a / gcd(a, b)) * b;
}

// 再帰による定義
unsigned int gcd_r(const unsigned int a, const unsigned int b)
{
    if (b == 0) return a;
    else return gcd_r(b, a % b);
}

// 再帰版gcdを使うバージョン
unsigned int lcm_r(const unsigned int a, const unsigned int b) {
    if ( a == 0 || b == 0)
    return 0;

    return (a / gcd_r(a, b)) * b;
}

int main() {
    unsigned int n = 1;
    // ループの範囲は2以上20未満でいいのだけど、ここは文字通りに実装
    for (unsigned int i = 1; i < 21; i++) {
        n = lcm(n, i);
        printf("%d\t", n);
    }
    printf("\nAnswer = %d\n", n);

    n = 1;
    for (unsigned int i = 1; i < 21; i++) {
        n = lcm_r(n, i);
        printf("%d\t", n);
    }
    printf("\nAnswer = %d\n", n);
}
