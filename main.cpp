//In The Name Of GOD
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<Windows.h>
#include"MapEditor.h"

#define MAXN  512

int rel[MAXN][MAXN], remain[MAXN][MAXN];
int IsSingle;

int main() {
    system("cls");
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes; 
    SetConsoleTextAttribute ( h, FOREGROUND_BLUE);
    Print("Hi.\nMy name is Farshid, I'm the developer of this program. It's my universoty final project.\nI hope you enjoy it!\n");
    Print("Lets begin.\nDo you want to use the Map editor or not?\n[1]Yes\n[2]No\n");
    int tmp, len; scanf("%d", &tmp);
    if (tmp == 1)
        RunMapEditor();
    FILE* fr = fopen("map.bin", "rb");
    fread(&len, sizeof(int), 1, fr);
    for (int i = 0; i < len; i++) {
        char tmp2[MAXN];
        fread(tmp2, sizeof(char), len, fr);
        for (int j = 0; j < len; j++)
            rel[j][len - i - 1] = tmp2[j] - '0';
    } 
    system("cls");
    Print("Welcome to the game\n");
    printf("[1]Load\n");
    printf("[2]New single player game\n");
    printf("[3]New Multiplayer game\n");
    printf("[4]Exit");
    scanf("%d", &tmp);
    
}