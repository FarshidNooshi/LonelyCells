//In The Name Of GOD
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<Windows.h>
#include"linklist.h"
#include"MapEditor.h"
#include"SingleMode.h"

#define MAXN  512

#ifndef DEBUG
typedef struct cell cell;
struct cell {
    char name[6];
    int x = -1, y = -1, sc = 0;
    cell* nxt;
} *lst;
#define DEBUG
#endif

enum blocks { ENERGY = 1, MITOSIS, FORBIDDEN, NORMAL};

int rel[MAXN][MAXN], remain[MAXN][MAXN], len;
int IsSingle, Z,  n = 3;
char table[MAXN][MAXN][3];

void _();

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
    init(table, len);
    Z = 4 * len + 3;
    system("cls");
    Print("Welcome to the game\n");
    printf("[1]Load\n");
    printf("[2]New single player game\n");
    printf("[3]New Multiplayer game\n");
    printf("[4]Exit\n");
    scanf("%d", &tmp);
    if (tmp == 2)
        start(table, &lst, len, rel, h, wOldColorAttrs);

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