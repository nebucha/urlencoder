#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 102400

int main(int argc, char *argv[])
{
    char buf[BUFFSIZE];
    char *c2p[256];
    FILE *fp = NULL;
    char *filename = NULL;

    // 引数にファイル名が指定されていれば、ファイルから読み込む
    // ファイル名が指定されていなければ、標準入力から読み込む
    if (argc == 2) {
        filename = argv[1];
        if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "File open error: %s\n", filename);
        exit(1);
        }
    } else {
        fp = stdin;
    }

    // デフォルトの変換: % + 16進数表記
    for (int i = 0; i < 256; i++) {
        c2p[i] = (char *)malloc(4);
        sprintf(c2p[i], "%%%02X", i);
    }
    // 数字: そのまま
    for (int i = 48; i < 58; i++)
        sprintf(c2p[i], "%c", i);
    // アルファベット: そのまま
    for (int i = 65; i < 91; i++)
        sprintf(c2p[i], "%c", i);
    for (int i = 97; i < 123; i++)
        sprintf(c2p[i], "%c", i);
    // 半角スペース: '+'に変換
    c2p[' '] = "+";
    // そのまま出力する文字
    c2p['-'] = "-";
    c2p['.'] = ".";
    c2p['_'] = "_";
    c2p['~'] = "~";

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        for (int i = 0; buf[i] != '\n'; i++) {
            printf("%s", c2p[buf[i]]);
        }
    }    
}