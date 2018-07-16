/*
マクロ DEBUG が定義されているときは与えた文字列を表示し、
定義されていないときは何もしないマクロを作成せよ。
*/
#include <stdio.h>

#define DEBUG
/*
    マクロ定義時に条件分けしないと、ソースコードに#if defined〜を記述することになる
    また、何もしない場合に何も定義しないとif〜else文で不具合が発生する
*/
#if defined(DEBUG)
#define debugp(s) printf(s)
#else
#define debugp(s) do {} while(0)
#endif

int main() {
    debugp("debug debug\n");
}