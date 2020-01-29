//In The Name Of GOD
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<Windows.h>
#include"functions.h"
#include"linklist.h"
#include"MapEditor.h"
#include"MultiMode.h"
#include"SingleMode.h"

#ifndef DEBUG
typedef struct cell cell;
struct cell {
    char name[6];
    int x = -1, y = -1, sc = 0;
    cell* nxt;
} *lst;
#define DEBUG
#endif

int rel[MAXN][MAXN], remain[MAXN][MAXN], len;
int Z,  n = 3, turn, agnst;
char table[MAXN][MAXN][3];

int main() {
    system("cls");
    srand(time(NULL));
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes; 
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    Print("Hi.\nMy name is Farshid, I'm the developer of this program. It's my universoty final project.\nI hope you enjoy it!\n");
    Print("Lets begin.\nDo you want to use the Map editor or not?\n[1]Yes\n[2]No\n");
    int tmp; scanf("%d", &tmp);
    if (tmp == 1)
        RunMapEditor(table, wOldColorAttrs);
    _();
    Z = 4 * len + 3;
    init(table, len);
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            AddToTable(i, j, rel[i][j], 100, len, table);
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            if (rel[i][j] == ENERGY)
                remain[i][j] = 100;
    system("cls");
    PRint(table, Z, h, wOldColorAttrs);
    Print("Welcome to the game\n");
    printf("[1]Load\n");
    printf("[2]New single player game\n");
    printf("[3]New Multiplayer game\n");
    printf("[4]Exit\n");
    scanf("%d", &tmp);
    if (tmp == 2)
        start(table, len, rel, remain, h, wOldColorAttrs, 1, 0);
    else if (tmp == 4) 
        return 0;
    else if (tmp == 1) {
        len = LoadRead(rel, remain, table);
        agnst = len % 2, len /= 2;
        turn = len % ZZ, len = len / ZZ;
        if (len % 2) {
            len /= 2;
            start2(table, len, rel, remain, h, wOldColorAttrs, 0, turn, 1, agnst);
        } else {
            len /= 2;
            start(table, len, rel, remain, h, wOldColorAttrs, 0, 0);
        }
    } else 
        start2(table, len, rel, remain, h, wOldColorAttrs, 1, 0, 1, agnst);
    SetConsoleTextAttribute ( h, wOldColorAttrs);
    return 0;
}

void _() {
    FILE* fr = fopen("map.bin", "rb");
    fread(&len, sizeof(int), 1, fr);
    for (int i = 0; i < len; i++) {
        char tmp2[MAXN];
        fread(tmp2, sizeof(char), len, fr);
        for (int j = 0; j < len; j++)
            rel[j][len - i - 1] = tmp2[j] - '0';
    } 
    fclose(fr);
}