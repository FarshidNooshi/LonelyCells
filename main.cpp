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

struct Cell {
    int x, y;
    char* s;
    size_t sz;
    sCell* nxt;
};

struct table {
    int state;
};

sCell* lst[2];//سلول ها 
stable Tbl[MAXN][MAXN];
bool mark[MAXN][MAXN];
int n;
FILE* f1;

void CreateNew(sCell**);
void MyRead(int );
void RunSingleMode();
void RunMultiMode();
void init(sCell* , int);
void BuildCells(int);

int main() {
    srand(time(NULL));
    MyRead(0);
    printf("[1]Load\n");
    printf("[2]New Single player game\n");
    printf("[3]New Multiplayer game\n");
    printf("[4]Exit\n");
    int tmp;    scanf("%d", &tmp);
    if (tmp == 1) 
        MyRead(1);
    else if (tmp == 2) 
        RunSingleMode();
    else if (tmp == 3) 
        RunMultiMode();
    return 0;
}

void CreateNew(sCell** mem) {
    sCell* t = *mem;
    sCell* tmp = (sCell*)malloc(sizeof(sCell));
    tmp->nxt = NULL;
    t->nxt = tmp;
}

void BuildCells(int t) {
    int m;  scanf("%d", &m);
    sCell* ptr = lst[t];
    size_t len = 5;
    for (int i = 0; i < m; i++) {
        CreateNew(&ptr);
        init(ptr, len);
        ptr->x = rand() % n, ptr->y = rand() % n;
        while (mark[ptr->x][ptr->y])
            ptr->x = rand() % n, ptr->y = rand() % n;
        mark[ptr->x][ptr->y] = 1;
    }
}

void RunSingleMode() {
    BuildCells(0);
}

void RunMultiMode() {
    BuildCells(0);
    BuildCells(1);
    printf("Do you want to play against computer?\ny = YES, n = NO\n");
    char tmp;   scanf("%c", &tmp);
    int flag = 0;
    while (1) {
        if (tmp == 'y') {
            if (flag % 2) 
                CTurn();
            else {
                
            } 

        }
    }
}

void init(sCell* ptr, size_t size) {
    ptr->s = malloc((size + 1) * sizeof(char));
    ptr->sz = size;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < size; i++) {
        int key = rand() % (sizeof(charset) / sizeof(char) - 1);
        ptr->s[i] = charset[key];
    }
    ptr->s[size] = '\0';
}

void MyRead(int flag) {
    f1 = fopen("map.bin", "rb");
    if (fread(&n, sizeof(int), 1, f1) < 1) {
        printf("Error occured\n");
        exit(0);
    }
    for (int i = 0; i < n; i++) {
        char state[MAXN];
        fread(state, sizeof(char), n, f1);
        for (int j = 0; j < n; j++)
            Tbl[i][j].state = state[j] - '0';
    }
    fclose(f1);
    if (flag) {
        ...
    }
}