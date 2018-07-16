/*
  左右どちらから読んでも同じ値になる数を回文数という.
  2桁の数の積で表される回文数のうち, 最大のものは 9009 = 91 × 99 である.
  では, 3桁の数の積で表される回文数の最大値を求めよ.
*/
/*
    C++ならstd::stringを使用するという手もあるが、Cではそれは手間がかかりすぎる
    本問題は、回文数をどうやって見つけるか、また処理をいかに速くするか、を
    考えるものである（まぁ、簡単なんですけどね）
*/
#include <stdio.h>

// 数値並びを逆にした数値をつくる
unsigned int reverse(unsigned int org) {
    unsigned int dst = 0;
    while (org != 0) {
        dst *= 10;
        dst += (org % 10);
        org /= 10;
    }
    return dst;
}

/*
    最大のものを求めると言われたのだから、最大値から降順で検索（i）
    掛け合わせる数値（j）は、降順でiまで検索することで、二重検索を防ぐ
    正直なところ、回文数を発見した時点でbreakし、returnは一箇所にすべき
*/
int main() {
    unsigned int r = 0;
    for (unsigned int i = 999; i > 99; i-- ) {
        for (unsigned int j = 999; j >= i; j--) {
            unsigned int m = i * j;
            if (m == reverse(m)) {
                if (r < m) r = m;
                printf("%d x %d = %d : reverse = %d\n",i, j, m, reverse(m));
                break;
            }
        }
    }
    printf("result = %d\n", r);
}