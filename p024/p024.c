/*
順列とはモノの順番付きの並びのことである. たとえば, 3124は数 1, 2, 3, 4 の一つの順列である. すべての順列を数の大小でまたは辞書式に並べたものを辞書順と呼ぶ. 0と1と2の順列を辞書順に並べると
012 021 102 120 201 210
になる.

0,1,2,3,4,5,6,7,8,9からなる順列を辞書式に並べたときの100万番目はいくつか?
*/

/*
正直にすべてのケースを作成するとメモリが足りなくなるか時間がかかりすぎるはず、多分ｗ
法則を見つける・・・
ｎ個の数字があるとき総数はn!個。
先頭一文字あたりn!/n=(n-1)!個。
となると、先頭２文字を確定させると(n-2)!個。
つまり、先頭m文字を確定させると(n-m)!個。

x番目を指定するなら、xを超えない(n-m)!を探してそこから再帰的に順列を決めていけばいいはず。
ということは、x番目を超えない(n-m)!のロジックがミソになるはず！
*/

#include <stdio.h>

#define MAX 10

/*
    v:順列を構成する数字を格納
    ar:求めるべき順列
    再帰計算を使用するため面倒くさいのでグローバル変数
*/
int v[MAX];
int ar[MAX];

/*
    fact:ただの階乗計算
    数値の範囲的にintでオッケー
*/
int fact(const int n) {
    int rc = 1;
    for (int i = 1; i <= n; i++) {
        rc *= i;
    }
    return rc;
}

/*
  miso:辞書順の指定された順番目の数値を求める
  本関数ではすべての数値を０ベースで演算することでわかりやすくしている（つもり）
    n:    残りの桁数
    x:    現桁数での順番
    left: 確定している桁数
*/
void miso(const int n, const int x, const int left) {
    int k = fact(n-1);  // 現桁数での組み合わせ数（複数回（と言っても２回だけれど）使うので計算は一度だけにする）
    int idx = x / k;    // 現桁数での数字の順序
    int am = x % k;     // 現桁数での確定した数字の何番目か

    ar[left] = v[idx];  // 今回はこの数字を使用
    // 使った数字は２度と使わないため消去
    for (int i = idx; i < MAX-1-left; i++) {    //-left入れなくても辻褄は合う
        v[i] = v[i+1];                          // 詰めていくので終了条件から-1しておく
    }
    if (n == 1) return;
    miso(n-1, am, left+1);
}

int main() {
/*
    for (int index = 1; index <= fact(MAX); index++) {
        printf("%d", index);
        int amari = index % 10;
        switch(amari) {
            case 1:
                printf("st : ");
                break;
            case 2:
                printf("nd : ");
                break;
            case 3:
                printf("rd : ");
                break;
            default:
                printf("th : ");
                break;
        }
        for (int i = 0; i < MAX; i++) {
            v[i] = i;
            ar[i] = 0;
        }
        miso(MAX, index-1, 0);  // 2番目の引数は計算を０ベースで行うためマイナス１
        for (int i = 0; i < MAX; i++) {
            printf("%d", ar[i]);
        }
        printf("\n");
  }
*/

    for (int i = 0; i <= MAX-1; i++) {
        v[i] = i;
        ar[i] = 0;
    }
    miso(MAX, 1000000-1, 0);    // スタートは０番目なので-1
    for (int i = 0; i < MAX; i++) {
        printf("%d", ar[i]);
    }
    printf("\n");
}
