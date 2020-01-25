//In The Name Of GOD
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"READER.h"
#include"Computer.h"
#include"MapEditor.h" 
#include"GraphicPrint.h"

#define MAXN 128

typedef struct Cell     sCell;
typedef struct table    stable;

enum blocks { ENERGY = 1, MITOSIS, FORBIDDEN, NORMAL };

struct String {
    char s[MAXN];
    int sz;
};

struct Cell {
    int x, y;
    String name;
    sCell* nxt;
};

struct table {
    int state;
};

sCell* lst;//سلول ها 
stable Tbl[MAXN][MAXN];
int n;
FILE* f1;

void MyRead();

int main() {
    MyRead();
}

void MyRead() {
    f1 = fopen("map.bin", "rb");
    if (fread(&n, sizeof(int), 1, f1) < 1) {
        printf("Error occured\n");
        return 0;
    }
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        char state[MAXN];
        fread(state, sizeof(char), n, f1);
        for (int j = 0; j < n; j++)
            Tbl[i][j].state = state[j] - '0';
    }
    fclose(f1);
}