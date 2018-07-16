/*
以下の4言語、4つの挨拶を対話的に表示するプログラムを作成せよ

| 　　 |  日本語   |     英語      | フランス語  |    ドイツ語      |
|:---:|:--------:|:------------: |:---------:|:--------------:|
| 朝　 | おはよう　 | Good moring  |  Bonjour  |  Guten Morgen   |
| 昼　 | こんにちは |    Hello     |  Bonjour  |    Guten Tag    |
| 夜　 | こんばんは | Good evening |  Bonsoir  |   Guten Abend   |
| 別れ | さようなら |   Good-by    | Au revoir | Auf Wiedersehen |

プログラムは、
1. 最初の入力で言語選択
1. 次の選択でシチュエーション選択
1. 最初に戻る、または終了

- ユーザインタフェースはご自由に！
- 拡張性を考慮すること
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    全メッセージをRAM内に内蔵する場合：

    char *mes_01_ja = "おはよう";
    char *mes_02_ja = "こんにちは";
    ・・・
    と定義し、
    char *ja[] = {mes_01_ja, mes_02_ja,...};    //　実行時のみ実現可能
    とすると、余計なメモリを消費する（コンパイラが最適化してくれるかも？）。
    メッセージ数が多くて、追加したメッセージに不足が出るのが怖いのなら
    マクロ定義にするか、コメントで番号を振ればいい。
*/

char *ja[] = {"おはよう", "こんにちは", "こんばんは", "さようなら"};
char *en[] = {"Good moring", "Hello", "Good evening", "Good-by"};
char *fr[] = {"Bonjour", "Bonjour", "Bonsoir", "Au revoir"};
char *gr[] = {"Guten Morgen", "Guten Tag", "Guten Abend", "Auf Wiedersehen"};

char **message[] = {ja, en, fr, gr};
char *lang_name[] = {"日本語", "English", "Français", "Deutsch"};

// UI用
// 標準入力より文字列取得
char *get_string(char *s, int n) {
    if (fgets(s, n, stdin) == NULL) return NULL;
    char *ln = strchr(s, '\n');
    if (ln) {
        *ln = '\0';
    } else {
        while (1) {
            int c = getchar();
            if (c == '\n' || c == EOF) break;
        }
    }
    return s;
}

// UI用
// メニュー表示とユーザの選択の実行・表示
int get_id(char *title, char *disp[], int max) {
    #define MAX_BUF 10  // C11 ?
    char buf[MAX_BUF];
    int id;
    for(;;) {
        printf("select %s\n", title);
        for (int i = 0; i < max; i++) {
            printf("%s = %d, ", disp[i], i+1);
        }
        printf("end = 9 : ");
        if (get_string(buf, MAX_BUF) == NULL) continue;
        id = atoi(buf);
        if (id > 0 && id <= max) {
            return id;
        }
        if (id == 9) return id;
    }
}

// データ構造がほぼ問題を解決してる？
void no01() {
    // messageには言語（ごとのメッセージ）の配列
    // メッセージの数は言語ごとのメッセージ
    // （変数名の命名が悪い例になってしまった？）
    const int max_language = sizeof(message) / sizeof(char*);
    const int max_message = sizeof(ja) / sizeof(char*);

    // magical number(1)が気持ち悪い
    //  ja_namesをjaの０番目にするとスッキリ？
    for (;;) {
        const int language_id = get_id("language", lang_name, max_language);
        if (language_id == 9) return;
        const int message_id = get_id("message", message[language_id-1], max_message);
        if (message_id == 9) return;
        printf("%s\n", message[language_id-1][message_id-1]);
    }
}
/*
    別空間のメモリや記憶装置にメッセージが格納＝必要な言語のみを動的に読み込む場合：
    通常は言語設定は、めったに実施しないからこっちが現実的？
    ファイルから読もうが何から得ようが、方法が違うだけでメッセージを扱う基本部分は同じ
*/
void no02() {
    const int max_language = sizeof(message) / sizeof(char*);
    const int max_message = sizeof(ja) / sizeof(char*);

    for (;;) {
        const int language_id = get_id("language", lang_name, max_language);
        if (language_id == 9) return;
        /*
            ここではすでにある配列からメッセージを得ているが
            これは
                my_message = get_message_table(language_id);
            という関数を作って、目的の言語のメッセージのみ取り出しているのと同義
        */
        char **my_message = message[language_id-1];
        const int message_id = get_id("message", my_message, max_message);
        if (message_id == 9) return;
        printf("%s\n", my_message[message_id-1]);
    }
}
/////////////////////////////////////////
//
// main関数
//
/////////////////////////////////////////
int main() {
//    no01();
    no02();

    return 0;
}
