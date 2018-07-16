/*
5000個以上の名前が書かれている46Kのテキストファイル names.txt を用いる. まずアルファベット順にソートせよ.

のち, 各名前についてアルファベットに値を割り振り, リスト中の出現順の数と掛け合わせることで, 名前のスコアを計算する.

たとえば, リストがアルファベット順にソートされているとすると, COLINはリストの938番目にある. またCOLINは 3 + 15 + 12 + 9 + 14 = 53 という値を持つ. よってCOLINは 938 × 53 = 49714 というスコアを持つ.

ファイル中の全名前のスコアの合計を求めよ.
*/
/*
    名前はアルファベット（半角文字列）で
    ダブルクォーテーション（"）で囲まれており、
    各名前はコンマ（,）で区切られている
    空白文字は存在しない
    ことが保証されている前提
*/
/*
TODO: ファイルサイズが大きくて一度に読み込めない場合の処理
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// ここではエラーが起きたら終了することにした
#define ERR_PRINTF_EXIT(...) do { fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE); } while(0)

// 一気にプログラムを作成すれば必要ない関数
// 余計なI/Oをするのは良くないけど、安全に動く・修正に耐えるプログラムという視点では
// 必要だと思う
long get_file_size(const char *filename) {
    struct stat stbuf;
//    int fd;

    const int fd = open(filename, O_RDONLY);
    if (fd == -1) { // error
        ERR_PRINTF_EXIT("open: can not open\n");
    }
    if (fstat(fd, &stbuf) == -1) {
        close(fd);
        ERR_PRINTF_EXIT("fstat: can not get status\n");
    }
    close(fd);
    return stbuf.st_size;
}

// 必要なときにI/Oするパターン
void file_read(const char *filename, char *buffer, const size_t buffer_size) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        ERR_PRINTF_EXIT("fopen: can not open\n");
    }
    char *rc = fgets(buffer, buffer_size, fp);
    if (rc == NULL) {
        fclose(fp);
        ERR_PRINTF_EXIT("fgets: can not read\n");
    }
    fclose(fp);
}
// データがファイルとして存在しているかこのように実装
// 通信とかでストリーミングのときは違う設計が必要
int count_names(char *buffer, const int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (buffer[i] == ',') {
            count++;
        }
    }
    return count + 1;   // 最後の名前のぶんを足す
}

// 最初を除いて、名前がスタートするトリガーは「,」であるという点に着目した
// もっと工夫が必要かも
void get_individual(char *buffer, const int buffer_size, char **name) {
    bool flag = true;   // 次は新しい名前を示すフラグ:状態のフラグ管理は悪手
    int c = 0;
    for (int i = 0; i < buffer_size; i++) {
        if (buffer[i] == '\"') {
            buffer[i] = '\0';
            if (flag == true) {
                name[c] = buffer+i+1;
                c++;
                flag = false;
            }
        }
        if (buffer[i] == ',') {
            buffer[i] = '\0';
            flag = true;
        }
    }
}

// qsortを使うため
int compare_char(const void * left, const void * right) {
    const char *left_char = *(const char **)left;
    const char *right_char = *(const char **)right;
    return strcmp(left_char, right_char);
}

// 個々の名前に対する計算
int calc(char *name) {
    int sum = 0;
    for (int i = 0; i < strlen(name); i++) {
        sum += name[i] - 'A' + 1;
    }
    return sum;
}

/*
    本プログラムでは元のデータの塊（buffer）を保持し
    （ただし、文字列の特性上少し加工はする）
    個々のデータ（名前）へのポインタたち（name）を操作する作戦
*/
    int main() {
    const long file_size = get_file_size("names.txt");
    if (file_size == 0) {
        ERR_PRINTF_EXIT("error\n");
    }
    char *buffer = malloc(file_size);
    if (buffer == NULL) {
        ERR_PRINTF_EXIT("malloc: error");
    }
    file_read("names.txt", buffer, file_size);
    const int count = count_names(buffer, file_size);

    char* *name = malloc(count*sizeof(char*)); //C11ならchar *name[count]
    if (name == NULL) {
        free(buffer);
        ERR_PRINTF_EXIT("malloc: error");
    }

    get_individual(buffer, file_size, name);

    qsort(name, count, sizeof(*name), compare_char);

    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += calc(name[i]) * (i + 1);
    }

    printf("result = %d\n", sum);

    free(name);
    free(buffer);
}
